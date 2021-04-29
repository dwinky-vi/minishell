/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:42:48 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/29 05:18:31 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_vars		vars;
	t_history	history;
	// char		*str;
	// char		*line;
	// int		cursor_pos;

	preparing(argc, argv, envp, &vars);
	get_history(&history, &vars);
	ft_termcap(&history, &vars);
	// str = (char *)ft_calloc(4096, 1);
	// line = (char *)ft_calloc(4096, 1);
	// cursor_pos = 0;
	// while (strcmp(str, "\4"))
	// {
	// 	print_prompt();
	// 	while (strcmp(str, "\n"))
	// 	{
	// 		if (read(0, str, 4096) == -1)
	// 			exit(FAILURE_CODE);
	// 		if (is_signal(str) == TRUE)
	// 		{
	// 			if (make_signal(str, &line, &cursor_pos, &history) == 1)
	// 				break ;
	// 		}
	// 		else if (is_up_or_down_key(str))
	// 			make_up_or_down(str, &line, &cursor_pos, &history);
	// 		else if (is_bonus_key(str) == TRUE)
	// 			make_bonus(str, line, &cursor_pos);
	// 		else if (!strcmp(str, KEY_BACKSPACE_FT) || !strcmp(str, KEY_DELETE_FT))
	// 			key_backspace_or_delete(str, &line, &cursor_pos, &history.arr[history.current]);
	// 		else
	// 		{
	// 			if (!strcmp(str, "\n"))
	// 				performing(line, &cursor_pos, &vars, &history);
	// 			else if ((size_t)cursor_pos < ft_strlen(line))
	// 				insert_inside(str, &line, &cursor_pos, &history);
	// 			else
	// 				write_characters(str, &line, &cursor_pos, &history);
	// 		}
	// 		ft_bzero(str, ft_strlen(str));
	// 	}
	// }
	return (return_func(&vars, &history));
}

// << >

// echo $"PATH"											!!!!!!!!!!!!!!!!!!!!!

// echo hello >| file

// echo ||  ;											!!!!!!!!!!!!!!!!!!!!!

// echo!2
