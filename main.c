/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:42:48 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/23 04:15:44 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	func_for_signal(int param)
{
	signal (SIGQUIT, SIG_IGN);
	signal (SIGINT, SIG_IGN);
	// signal (SIGTERM, SIG_IGN);    			// !!! Игнорирует сигнал прерывания процесса  (ЗАЩИТА ОТ kill minishell) !!!
}

void	clear_terminal_before_promt(int cursor_pos, char *previous_history)
{
	int len;

	if (previous_history == NULL)
		len = 0;
	else
		len = ft_strlen(previous_history);
	while (cursor_pos < len)
	{
		tputs(cursor_right, 1, ft_putchar);
		cursor_pos++;
	}
	while (cursor_pos > 0)
	{
		tputs(cursor_left, 1, ft_putchar);
		tputs(delete_character, 1, ft_putchar);
		cursor_pos--;
	}
}

int main(int argc, char **argv, char **envp)
{
	t_vars	vars;
	char	**history;
	char	*str;
	int		r;
	size_t	history_size;
	size_t	k;
	char	*line;
	int		cursor_pos;
	int		fd2;

	if (argc == 2 && ft_strnstr(argv[1], "child", BUFSIZE))			//!!!
		vars.miniflag = 1;											//!!!
	envp_copy(&vars, envp);									//!!!

    vars.list_env = get_env(vars.envp);
	init_term(&vars.term, get_term_name(vars.list_env));
	init_env(&vars);												//!!!
	str = (char *)ft_calloc(2000, 1);
	fd2 = open("testing", O_CREAT | O_RDWR | O_APPEND, 0600);
	k = 0;

	signal(SIGINT, &func_for_signal); // Это ловит ctrl-C.  Код сигнала –– 2
	signal(SIGQUIT, &func_for_signal); // Это ловит ctrl-\. Код сигнала –– 3
	int start_k = get_history(&history, &k, &vars); // leaks!!!!!!!!!!!!
	history_size = k;
	line = (char *)ft_calloc(2000, 1);
	cursor_pos = 0;
	char *old_history_line;

	old_history_line = NULL;
	vars.tmp_fd_0 = dup(0); //				!!! Запоминаю stdin fd !!!
	vars.tmp_fd_1 = dup(1); //				!!! Запоминаю stdin fd !!!
	while (strcmp(str, "\4"))
	{
		print_prompt();
		while (strcmp(str, "\n"))
		{
			dup2(vars.tmp_fd_0, 0); //				!!! Возвращаю stdin fd после пайпа !!!
			r = read(0, str, 100);
			if (!strcmp(str, "\4")) // ctrl-D
			{
				if (line[0] == '\0')
				{
					ft_putstr_fd("exit\n", 1);
					break ;
				}
				else
					pressed_key_delete(&cursor_pos, &line, &history[k]);
			}
			else if (!strcmp(str, "\e[A")) // UP
			{
				clear_terminal_before_promt(cursor_pos, history[k]);
				cursor_pos = 0;
				if (k > 0)
					k--;
				free(old_history_line); // очищаем лики
				old_history_line = ft_strdup(history[k]);
				if (history_size != 0)
				{
					ft_putstr_fd(history[k], 1);
					free(line);
					line = ft_strdup(history[k]);
					cursor_pos = ft_strlen(history[k]);
				}
			}
			else if (!strcmp(str, "\e[B")) // DOWN
			{
				clear_terminal_before_promt(cursor_pos, history[k]);
				if (k < history_size)
					k++;
				if (history_size == 0)
					k = 0;
				free(old_history_line); // очищаем лики
				old_history_line = ft_strdup(history[k]);
				if (history[k] == NULL)
				{
					cursor_pos = 0;
					ft_bzero(line, ft_strlen(line));
				}
				else if (history_size != 0)
				{
					ft_putstr_fd(history[k], 1);
					cursor_pos = ft_strlen(history[k]);
					free(line);
					line = ft_strdup(history[k]);
				}
			}
			else if (!strcmp(str, "\e[D")) // LEFT
			{
				if (0 < cursor_pos)
				{
					tputs(cursor_left, 1, ft_putchar);
					cursor_pos--;
				}
			}
			else if (!strcmp(str, "\e[C")) // RIGHT
			{
				if (0 <= cursor_pos && cursor_pos < ft_strlen(line))
				{
					tputs(cursor_right, 1, ft_putchar);
					cursor_pos++;
				}
			}
			else if (!strcmp(str, "\e[3~")) // delete (удалить под курсором)
			{
				free(old_history_line);
				old_history_line = ft_strdup(history[k]);
				pressed_key_delete(&cursor_pos, &line, &history[k]);
			}
			else if (!strcmp(str, "\177")) // backspace
			{
				free(old_history_line);
				old_history_line = ft_strdup(history[k]);
				pressed_key_backspace(&cursor_pos, &line, &history[k]);
			}
			else if (is_hotkey(str)) // TAB и всякие спец символы
			{
			}
			else if (!strcmp(str, "\e[H")) /** курсор в начало строки **/
			{
				pressed_key_home(&cursor_pos, &line);
			}
			else if (!strcmp(str, "\e[F"))  /** курсор в конец строки **/
			{
				pressed_key_end(&cursor_pos, &line);
			}
			else
			{
				if (!strcmp(str, "\n"))
				{
					write(1, str, r);
					parser(ft_strtrim(line, " "), &vars);
					printf("status = %d\n", g_code);
					print_prompt();
					cursor_pos = 0;
					if (k != history_size) // это для истории. Когда мы нажимали на стрелочки
					{
						free(history[k]); // очищаем лики
						history[k] = ft_strdup(old_history_line); // Что с ликами??? ПРОВЕРИТЬ СУКА
						k = history_size;
						free(old_history_line);
						old_history_line = NULL;
					}
					if (strcmp(line, ""))
					{
						free(history[k]); // очищаем лики
						history[k] = ft_strdup(line);
						history_size++;
						k = history_size;
					}
					ft_bzero(line, ft_strlen(line)); // чтобы после enter строка очищалась
				}
				else if (cursor_pos < ft_strlen(line))
				{
					tputs(save_cursor, 1, ft_putchar);
					char *append;
					append = ft_strdup(line + cursor_pos);
					line[cursor_pos] = '\0';
					line = ft_strjoin_free(line, str, 1);
					line = ft_strjoin_free(line, append, 3);
					free(history[k]);
					history[k] = ft_strdup(line);
					tputs(delete_line, 1, ft_putchar);
					print_prompt();
					write(1, line, ft_strlen(line));
					tputs(restore_cursor, 1, ft_putchar);
					tputs(cursor_right, 1, ft_putchar);
					cursor_pos++;
				}
				else
				{
					write(1, str, r);
					cursor_pos += ft_strlen(str); // это для cmd+V. До этого было просто cursor_pos++
					line = ft_strjoin_free(line, str, 1);
					free(history[k]);
					history[k] = ft_strdup(line);
				}
			}
			ft_bzero(str, ft_strlen(str));
		}
	}
	k = 0;
	// while (history[k])
	// 	ft_putendl_fd(history[k++], 1);
	// ft_putendl_fd("*****************************", fd2);
	if (vars.miniflag != 1)	//										!!! Условие возврата настроек терминала !!!
		return_term(&vars.term);
	set_history(history, start_k, &vars);
	return (1); //													!!! Ctrl-D возвращает 1 !!!
}

// обрабатывать одинаково
// -|echo ; ;
// -|;

// если есть ошибка синтаксиса, то ничего не отсылается в логику
// echo ||  ;

// export lol=123 olo=$lol
// echo $olo