/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:42:48 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/28 21:44:06 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

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
	vars->tmp_fd_0 = dup(0); //				!!! Запоминаю stdin fd !!!
	vars->tmp_fd_1 = dup(1); //				!!! Запоминаю stdout fd !!!
	vars->f_pipe = FALSE;
	vars->f_redir_0 = FALSE;
	vars->f_redir_1 = FALSE;
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	t_vars		vars;
	t_history	history_t;
	char	*str;
	int		r;
	char	**history;
	size_t	history_size;
	size_t	k = 0;
	char	*line;
	int		cursor_pos;

	// preparing();
	check_argv(argc, argv, &vars);
	set_vars(&vars, envp);
	init_term(&vars.term, get_term_name(vars.list_env));
	get_history(&history_t, &vars);
	k = history_t.current;
	history = history_t.arr;
	history_size = k;
	str = (char *)ft_calloc(4096, 1);
	line = (char *)ft_calloc(4096, 1);

	char *old_history_line;
	old_history_line = NULL;
	cursor_pos = 0;
	g_code = 0;
	while (strcmp(str, "\4"))
	{
		print_prompt();
		while (strcmp(str, "\n"))
		{
			r = read(0, str, 4096);
			if (!strcmp(str, "\4")) // ctrl-D
			{
				if (line[0] == '\0')
				{
					ft_putstr_fd("exit\n", 1);
					break ;
				}
				else
					pressed_key_delete(&line, &cursor_pos, &history[k]);
			}
			else if (!strcmp(str, "\3")) // ctrl-C
			{
				ft_putchar_fd('\n', 1);
				print_prompt();
				cursor_pos = 0;
				ft_bzero(line, ft_strlen(line));
				g_code = 1;
				if (k == history_size)
				{
					free(history[k]);
					history[k] = NULL;
				}
				k = history_size;
				continue ;
			}
			else if (!strcmp(str, "\034")) // ctrl-\_
			{
				continue ;
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
				clear_command_line(cursor_pos, history_t.arr[k]);
				if (k < history_size)
					k++;
				if (history_size == 0)
					k = 0;
				free(old_history_line);
				old_history_line = ft_strdup(history_t.arr[k]);
				if (history_t.arr[k] == NULL)
				{
					cursor_pos = 0;
					ft_bzero(line, ft_strlen(line));
				}
				else if (history_size != 0)
				{
					ft_putstr_fd(history_t.arr[k], 1);
					cursor_pos = ft_strlen(history_t.arr[k]);
					free(line);
					line = ft_strdup(history_t.arr[k]);
				}
			}
			else if (!strcmp(str, "\e[D") || !strcmp(str, "\e[C"))
			{
				key_left_or_right(&cursor_pos, str, line);
			}
			else if (!strcmp(str, "\177") || !strcmp(str, "\e[3~"))
			{
				free(old_history_line);
				old_history_line = ft_strdup(history[k]);
				key_backspace_or_delete(str, &line, &cursor_pos, &history[k]);
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
					write(1, str, r);
					parser(line, &vars);
					// printf("status = %d\n", g_code);
					print_prompt();
					cursor_pos = 0;
					if (k != history_size) // это для истории. Когда мы нажимали на стрелочки
					{
						free(history[k]);
						history[k] = ft_strdup(old_history_line); // Что с ликами??? ПРОВЕРИТЬ СУКА
						k = history_size;
						free(old_history_line);
						old_history_line = NULL;
					}
					if (strcmp(line, ""))
					{
						free(history[k]);
						history[k] = ft_strdup(line);
						history_size++;
						k = history_size;
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
					if (str[0] != '\e')
						cursor_pos += ft_strlen(str); // это для cmd+V. До этого было просто cursor_pos++
					else
						cursor_pos++;
					line = ft_strjoin_free(line, str, 1);
					free(history[k]);
					history[k] = ft_strdup(line);
				}
			}
			ft_bzero(str, ft_strlen(str));
		}
	}
	if (vars.miniflag != 1)
		return_term(&vars.term);
	set_history(&history_t, &vars);
	return (FAILURE_CODE); //													!!! Ctrl-D возвращает 1 !!!
}

// << >

// echo $"PATH"																!!!!!!!!!!!!!!!!!!!!!!!!1

// echo hello >| file

// echo ||  ;																!!!!!!!!!!!!!!!!!!!!!!!!!

// echo!2
