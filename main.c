/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:42:48 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/29 01:28:37 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

#define KEY_UP_FT "\e[A"
#define KEY_DOWN_FT "\e[B"
void	check_argv(int argc, char **argv, t_vars *vars)
{
	if (argc == 2 && ft_strnstr(argv[1], "child", BUFSIZE))
		vars->miniflag = 1;
}

int	set_vars(t_vars *vars, char **envp)
{
	envp_copy(vars, envp);
	get_env_to_lst(vars);
	init_env(vars);
	vars->export = NULL;
	vars->tmp_fd_0 = dup(0);
	vars->tmp_fd_1 = dup(1);
	vars->f_pipe = FALSE;
	vars->f_redir_0 = FALSE;
	vars->f_redir_1 = FALSE;
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	t_vars		vars;
	t_history	history;
	char	*str;
	char	*line;
	int		cursor_pos;
	char	*old_history_line;

	// preparing();
	check_argv(argc, argv, &vars);
	set_vars(&vars, envp);
	init_term(&vars.term, get_term_name(vars.list_env));
	get_history(&history, &vars);
	str = (char *)ft_calloc(4096, 1);
	line = (char *)ft_calloc(4096, 1);

	old_history_line = NULL;
	cursor_pos = 0;
	g_code = 0;
	while (strcmp(str, "\4"))
	{
		print_prompt();
		while (strcmp(str, "\n"))
		{
			if (read(0, str, 4096) == -1)
				exit(FAILURE_CODE);
			// printf("first = %d\n", (int)str[0]);
			// printf("second = %d\n", (int)str[1]);
			if (!strcmp(str, "\4")) // ctrl-D
			{
				// if (signal_ctrl_d(&line, &cursor_pos, &history) == FAILURE_CODE)
					// break ;
				if (line[0] == '\0')
				{
					ft_putstr_fd("exit\n", 1);
					break ;
				}
				else
					pressed_key_delete(&line, &cursor_pos, &history.arr[history.current]);
			}
			else if (!strcmp(str, "\3")) // ctrl-C
			{
				signal_ctrl_c(&line, &cursor_pos, &history);
			}
			else if (!strcmp(str, "\034")) // ctrl-\.
			{
			}
			else if (!strcmp(str, KEY_UP_FT))
			{
				pressed_key_up(&line, &cursor_pos, &history, &old_history_line);
			}
			else if (!strcmp(str, KEY_DOWN_FT))
			{
				pressed_key_down(&line, &cursor_pos, &history, &old_history_line);
			}
			else if (!strcmp(str, "\e[D") || !strcmp(str, "\e[C"))
			{
				key_left_or_right(&cursor_pos, str, line);
			}
			else if (!strcmp(str, "\177") || !strcmp(str, "\e[3~"))
			{
				free(old_history_line);
				old_history_line = ft_strdup(history.arr[history.current]);
				key_backspace_or_delete(str, &line, &cursor_pos, &history.arr[history.current]);
			}
			else if (!ft_strncmp(str, "\t", 1) || is_hotkey(str)) // TAB и всякие спец символы
			{
			}
			else if (!strcmp(str, "\e[H") || !strcmp(str, "\e[F"))
			{
				key_home_or_end(str, line, &cursor_pos);
			}
			else if (!strcmp(str, "\eb") || !strcmp(str, "\ef"))
			{
				move_word(str, line, &cursor_pos);
			}
			else
			{
				if (!strcmp(str, "\n"))
				{
					ft_putstr_fd(str, 1);
					parser(line, &vars);
					print_prompt();
					cursor_pos = 0;
					if (history.current != history.size) // это для истории. Когда мы нажимали на стрелочки
					{
						free(history.arr[history.current]);
						history.arr[history.current] = ft_strdup(old_history_line); // Что с ликами??? ПРОВЕРИТЬ СУКА
						history.current = history.size;
						free(old_history_line);
						old_history_line = NULL;
					}
					if (strcmp(line, ""))
					{
						free(history.arr[history.current]);
						history.arr[history.current] = ft_strdup(line);
						history.size++;
						history.current = history.size;
					}
					ft_bzero(line, ft_strlen(line)); // чтобы после enter строка очищалась
				}
				else if ((size_t)cursor_pos < ft_strlen(line))
				{
					tputs(save_cursor, 1, ft_putchar);
					char *append;
					append = ft_strdup(line + cursor_pos);
					line[cursor_pos] = '\0';
					line = ft_strjoin_free(line, str, 1);
					line = ft_strjoin_free(line, append, 3);
					free(history.arr[history.current]);
					history.arr[history.current] = ft_strdup(line);
					clear_command_line(cursor_pos, line);
					write(1, line, ft_strlen(line));
					tputs(restore_cursor, 1, ft_putchar);
					tputs(cursor_right, 1, ft_putchar);
					cursor_pos++;
				}
				else
				{
					ft_putstr_fd(str, 1);
					cursor_pos += ft_strlen(str); // это для cmd+V. До этого было просто cursor_pos++
					line = ft_strjoin_free(line, str, 1);
					free(history.arr[history.current]);
					history.arr[history.current] = ft_strdup(line);
				}
			}
			ft_bzero(str, ft_strlen(str));
		}
	}
	if (vars.miniflag != 1)
		return_term(&vars.term);
	set_history(&history, &vars);
	return (FAILURE_CODE);
}

// << >

// echo $"PATH"																!!!!!!!!!!!!!!!!!!!!!!!!1

// echo hello >| file

// echo ||  ;																!!!!!!!!!!!!!!!!!!!!!!!!!

// echo!2
