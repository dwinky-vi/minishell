/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_up_or_down.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 21:04:49 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/29 04:38:50 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

static void	pressed_key_up(char **line, int *cursor, t_history *history)
{
	if (history->current > 0)
	{
		clear_command_line(*cursor, history->arr[history->current]);
		*cursor = 0;
		if (history->current > 0)
			(history->current)--;
		if (history->size != 0)
		{
			ft_putstr_fd(history->arr[history->current], 1);
			free(*line);
			*line = ft_strdup(history->arr[history->current]);
			*cursor = ft_strlen(history->arr[history->current]);
		}
	}
}

static void	pressed_key_down(char **line, int *cursor, t_history *history)
{
	if (history->current < history->size)
	{
		clear_command_line(*cursor, history->arr[history->current]);
		if (history->current < history->size)
			history->current++;
		if (history->size == 0)
			history->current = 0;
		if (history->arr[history->current] == NULL)
		{
			*cursor = 0;
			ft_bzero(*line, ft_strlen(*line));
		}
		else if (history->size != 0)
		{
			ft_putstr_fd(history->arr[history->current], 1);
			*cursor = ft_strlen(history->arr[history->current]);
			free(*line);
			*line = ft_strdup(history->arr[history->current]);
		}
	}
}

int	is_up_or_down_key(char *str)
{
	if (!ft_strncmp(str, KEY_UP_FT, ft_strlen(KEY_UP_FT) + 1))
		return (TRUE);
	else if (!ft_strncmp(str, KEY_DOWN_FT, ft_strlen(KEY_DOWN_FT) + 1))
		return (TRUE);
	return (FALSE);
}

void	make_up_or_down(char *str, char **line, int *cursor, t_history *history)
{
	if (!ft_strncmp(str, KEY_UP_FT, ft_strlen(KEY_UP_FT) + 1))
		pressed_key_up(line, cursor, history);
	else if (!ft_strncmp(str, KEY_DOWN_FT, ft_strlen(KEY_DOWN_FT) + 1))
		pressed_key_down(line, cursor, history);
}
