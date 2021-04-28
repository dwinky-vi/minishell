/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_up_or_down.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 21:04:49 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/29 00:23:23 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	 pressed_key_up(char **line, int *cursor, t_history *history, char **old_history_line)
{
	if (history->current > 0)
	{
		clear_command_line(*cursor, history->arr[history->current]);
		*cursor = 0;
		if (history->current > 0)
			(history->current)--;
		free(*old_history_line);
		*old_history_line = ft_strdup(history->arr[history->current]);
		if (history->size != 0)
		{
			ft_putstr_fd(history->arr[history->current], 1);
			free(*line);
			*line = ft_strdup(history->arr[history->current]);
			*cursor = ft_strlen(history->arr[history->current]);
		}
	}
}

void	 pressed_key_down(char **line, int *cursor, t_history *history, char **old_history_line)
{
	if (history->current < history->size)
	{
		clear_command_line(*cursor, history->arr[history->current]);
		if (history->current < history->size)
			history->current++;
		if (history->size == 0)
			history->current = 0;
		free(*old_history_line);
		*old_history_line = ft_strdup(history->arr[history->current]);
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
