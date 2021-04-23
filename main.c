/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:42:48 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/23 22:18:54 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	check_argv(int argc, char **argv, t_vars *vars)
{

	if (argc == 2 && ft_strnstr(argv[1], "child", BUFSIZE))			//!!!
		vars->miniflag = 1;											//!!!
}

int	set_vars(t_vars *vars, char **envp)
{
	vars->envp = envp_copy(envp);								//!!!
	get_env_to_lst(vars);
	init_env(vars);												//!!!
	vars->f_pipe = FALSE;
	vars->f_redir = FALSE;
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	t_vars	vars;
	char	*str;
	int		r;
	char	**history;
	size_t	history_size;
	size_t	k;
	char	*line;
	int		cursor_pos;

	check_argv(argc, argv, &vars);
	set_vars(&vars, envp);
	signal_off();
	init_term(&vars.term, get_term_name(vars.list_env)); // поставить проверки на termcaps функции, они могут вернуть -1
	str = (char *)ft_calloc(4096, 1);
	k = 0;
	int start_k = get_history(&history, &k, &vars); // leaks!!!!!!!!!!!!
	history_size = k;
	line = (char *)ft_calloc(4096, 1);
	cursor_pos = 0;
	char *old_history_line;

	old_history_line = NULL;
	int		tmp_fd_0 = dup(0); //				!!! Запоминаю stdin fd !!!
	while (strcmp(str, "\4"))
	{
		print_prompt();
		while (strcmp(str, "\n"))
		{
			dup2(tmp_fd_0, 0); //				!!! Возвращаю stdin fd после пайпа !!!
			r = read(0, str, 4096);
			str[r] = '\0';
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
				clear_command_line(cursor_pos, history[k]);
				cursor_pos = 0;
				if (k > 0)
					k--;
				free(old_history_line);
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
				clear_command_line(cursor_pos, history[k]);
				if (k < history_size)
					k++;
				if (history_size == 0)
					k = 0;
				free(old_history_line);
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
			else if (!ft_strncmp(str, "\t", 1) || is_hotkey(str)) // TAB и всякие спец символы
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
					// printf("status = %d\n", g_code);
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
					clear_command_line(cursor_pos, line);
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
	if (vars.miniflag != 1)										//!!!!
		return_term(&vars.term);
	set_history(history, start_k, &vars);
	return (1); //													!!! Ctrl-D возвращает 1 !!!
}

// -|echo ; ;
// -|;
// >>>|;;
// << >
// < >>
// echo hello >| file              											!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// echo ||  ;
// export lol=123 olo=$lol
// echo $olo

// echo!2
// echo "123"'456' это один символ
// echo 'qwe'123
// echo "This $"
// echo " ' " " ' "
// export $qwe=123; echo "This \$qwe"\=$qwe\ \!
// export qwe=$; echo "This \$qwe"$qwePATH
