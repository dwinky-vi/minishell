/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:42:48 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/12 22:49:28 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	func_for_signal(int param)
{
	signal (SIGINT, SIG_IGN);
	if (param == 2)
		ft_putstr_fd("___^C", 1);
	else if (param == 3)
		ft_putstr_fd("___^\\", 1);
	else
		ft_putstr_fd("error\n", 1);
}

int main(int argc, char **argv, char **envp)
{
	struct termios	term;
	t_list			*head_env;
	char			**history;
	char			*str;
	int				r;
	size_t			history_size;
	size_t			k;
	char			*line;
	int				cursor_pos = 0;
	int				fd;

    head_env = get_env(envp);
	init_term(&term, get_term_name(head_env));
	str = (char *)ft_calloc(2000, 1);
	history_size = 0;
	fd = open("history_file", O_CREAT | O_RDWR | O_APPEND, 0600); //права доступа выдаются, как в bash
	int fd2 = open("testing", O_CREAT | O_RDWR, 0777);
	k = 0;

	// signal(SIGINT, &func_for_signal); // Это ловит ctrl-C.  Код сигнала –– 2
	// signal(SIGQUIT, &func_for_signal); // Это ловит ctrl-\. Код сигнала –– 3
	history = get_previous_history(fd, &k);
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
				tputs(delete_line, 1, ft_putchar);
				print_prompt();
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
				tputs(delete_line, 1, ft_putchar);
				print_prompt();
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
					parser(line, head_env, envp);
					print_prompt();
					cursor_pos = 0;
					if (k != history_size) // это для истории. Когда мы нажимали на стрелочки
						k = history_size;
					if (strcmp(line, ""))
					{
						history[k] = ft_strdup(line);
						write(fd, history[k], ft_strlen(history[k]));
						write(fd, "\n", 1);
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
					line = ft_strjoin(line, str);
					line = ft_strjoin(line, append);
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
	close(fd);
	return_term(&term);
	return (0);
}

// обрабатывать одинаково
// -|echo ; ;
// -|;

// если есть ошибка синтаксиса, то ничего не отсылается в логику
// echo ||  ;