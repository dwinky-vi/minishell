/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:42:48 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/16 18:04:07 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	write_bash_history(char **history, int k, int fd)
{
	while (history[k])
	{
		ft_putstr_fd(history[k], fd);
		ft_putchar_fd('\n', fd);
		k++;
	}
	close(fd);
}

void	func_for_signal(int param)
{
	signal (SIGINT, SIG_IGN);
	signal (SIGTERM, SIG_IGN);    			// игнорирует сигнал прерывания процесса  (ЗАЩИТА ОТ kill minishell)
	if (param == 2)
		ft_putstr_fd("___^C", 1);
	else if (param == 3)
		ft_putstr_fd("___^\\", 1);
	else
		ft_putstr_fd("error\n", 1);
}

int main(int argc, char **argv, char **envp)
{
	// struct termios	term;
	// t_list			*head_env;
	t_vars	vars;
	char	**history;
	char	*str;
	int		r;
	size_t	history_size;
	size_t	k;
	char	*line;
	int		cursor_pos = 0;
	int		fd;

	if (argc == 2 && ft_strnstr(argv[1], "child", BUFSIZE))			//!!!
		vars.miniflag = 1;											//!!!


	vars.envp = envp;
    vars.list_env = get_env(envp);
	init_term(&vars.term, get_term_name(vars.list_env));
	start_shlvl(&vars);
	str = (char *)ft_calloc(2000, 1);
	// history_size = 0;
	fd = open(".bash_history", O_CREAT | O_RDWR | O_APPEND, 0600); //права доступа выдаются, как в bash
	int fd2 = open("testing", O_CREAT | O_RDWR, 0777);
	k = 0;

	// signal(SIGINT, &func_for_signal); // Это ловит ctrl-C.  Код сигнала –– 2
	// signal(SIGQUIT, &func_for_signal); // Это ловит ctrl-\. Код сигнала –– 3
	int start_k = get_previous_history(&history, fd, &k); // leaks!!!!!!!!!!!!
	history_size = k;
	line = (char *)ft_calloc(2000, 1);
	cursor_pos = 0;
	while (strcmp(str, "\4"))
	{
		print_prompt();
		while (strcmp(str, "\n"))
		{
			r = read(0, str, 100);
			str[r] = '\0';
			if (!strcmp(str, "\4")) // ctrl-D
			{
				if (line[0] == '\0')
				{
					ft_putstr_fd("exit\n", 1);
					break ;
				}
				else
					pressed_key_delete(&cursor_pos, &line);
			}
			else if (!strcmp(str, "\e[A")) // UP
			{
				while (cursor_pos > 0)
				{
					tputs(cursor_left, 1, ft_putchar);
					tputs(delete_character, 1, ft_putchar);
					cursor_pos--;
				}
				// tputs(delete_line, 1, ft_putchar);
				// print_prompt();
				if (k > 0)
					k--;
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
				while (cursor_pos > 0)
				{
					tputs(cursor_left, 1, ft_putchar);
					tputs(delete_character, 1, ft_putchar);
					cursor_pos--;
				}
				// tputs(delete_line, 1, ft_putchar);
				// print_prompt();
				if (k < history_size)
					k++;
				if (history_size == 0)
					k = 0;
				if (k == history_size)
				{
					cursor_pos = 0;
					ft_bzero(line, ft_strlen(line));
				}
				else if (history_size != 0)
				{
					cursor_pos = ft_strlen(history[k]);
					ft_putstr_fd(history[k], 1);
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
				pressed_key_delete(&cursor_pos, &line);
			}
			else if (!strcmp(str, "\177")) // backspace
			{
				pressed_key_backspace(&cursor_pos, &line);
			}
			else if (!strcmp(str, "\t")) // TAB
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
					print_prompt();
					cursor_pos = 0;
					if (k != history_size) // это для истории. Когда мы нажимали на стрелочки
						k = history_size;
					if (strcmp(line, ""))
					{
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
					cursor_pos++;
					line = ft_strjoin_free(line, str, 1);
				}
			}
			ft_bzero(str, ft_strlen(str));
		}
	}
	if (vars.miniflag != 1)										//!!!!
		return_term(&vars.term);
	write_bash_history(history, start_k, fd);
	return (0);
}

// обрабатывать одинаково
// -|echo ; ;
// -|;

// если есть ошибка синтаксиса, то ничего не отсылается в логику
// echo ||  ;

// export lol=123 olo=$lol
// echo $olo