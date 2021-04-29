/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termcap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 05:18:12 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/29 20:14:25 by aquinoa          ###   ########.fr       */
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
	else if (!ft_strncmp(str, KEY_BACKSPACE_FT, ft_strlen(KEY_BACKSPACE_FT)) || \
				!ft_strncmp(str, KEY_DELETE_FT, ft_strlen(KEY_DELETE_FT)))
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
	else if (!ft_strncmp(str, KEY_BACKSPACE_FT, ft_strlen(KEY_BACKSPACE_FT)) || \
				!ft_strncmp(str, KEY_DELETE_FT, ft_strlen(KEY_DELETE_FT)))
		key_backspace_or_delete(str, line, cursor_pos, \
											&history->arr[history->current]);
	return (SUCCESS_CODE);
}

static int	read_line(char *str, char **line, t_history *history, t_vars *vars)
{
	int		cursor_pos;

	cursor_pos = 0;
	while (ft_strncmp(str, "\n", 1))
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
			if (!ft_strncmp(str, "\n", 1))
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
	while (ft_strncmp(str, "\4", 1))
	{
		print_prompt();
		if (read_line(str, &line, history, vars) == FAILURE_CODE)
			return ;
	}
}
