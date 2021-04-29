/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termcap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 05:18:12 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/29 19:31:27 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

static int	is_something(char *str)
{
	if (is_signal(str) == TRUE)
		return (TRUE);
	else if (is_up_or_down_key(str) == TRUE)
		return (TRUE);
	else if (is_bonus_key(str) == TRUE)
		return (TRUE);
	else if (!strcmp(str, KEY_BACKSPACE_FT) || !strcmp(str, KEY_DELETE_FT))
		return (TRUE);
	return (FALSE);
}

static int	do_something(char *str, char **line, int *cursor_pos, \
													t_history *history)
{
	if (is_signal(str) == TRUE)
	{
		if (make_signal(str, line, cursor_pos, history) == 1)
			return (FAILURE_CODE);
	}
	else if (is_up_or_down_key(str) == TRUE)
		make_up_or_down(str, line, cursor_pos, history);
	else if (is_bonus_key(str) == TRUE)
		make_bonus(str, *line, cursor_pos);
	else if (!strcmp(str, KEY_BACKSPACE_FT) || !strcmp(str, KEY_DELETE_FT))
		key_backspace_or_delete(str, line, cursor_pos, \
											&history->arr[history->current]);
	return (SUCCESS_CODE);
}

static int	read_line(char *str, char **line, t_history *history, t_vars *vars)
{
	int		cursor_pos;

	cursor_pos = 0;
	while (strcmp(str, "\n"))
	{
		if (read(0, str, 4096) == -1)
			exit(FAILURE_CODE);
		if (is_something(str) == TRUE)
		{
			if (do_something(str, line, &cursor_pos, history) == 1)
				return (FAILURE_CODE);
		}
		else
		{
			if (!strcmp(str, "\n"))
				performing(*line, &cursor_pos, vars, history);
			else if ((size_t)cursor_pos < ft_strlen(*line))
				insert_inside(str, line, &cursor_pos, history);
			else
				write_characters(str, line, &cursor_pos, history);
		}
		ft_bzero(str, ft_strlen(str));
	}
	return (FAILURE_CODE);
}

void	ft_termcap(t_history *history, t_vars *vars)
{
	char	*str;
	char	*line;

	str = (char *)ft_calloc(4096, sizeof(char));
	line = (char *)ft_calloc(4096, sizeof(char));
	while (strcmp(str, "\4"))
	{
		print_prompt();
		if (read_line(str, &line, history, vars) == FAILURE_CODE)
			return ;
	}
}
