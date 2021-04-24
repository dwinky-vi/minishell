/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_backspace_delete.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 19:14:34 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/24 20:29:28 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	pressed_key_backspace(int *cursor_pos, char **line, char **history_line)
{
	int	cur_pos;

	cur_pos = *cursor_pos;
	if (cur_pos > 0)
	{
		tputs(cursor_left, 1, ft_putchar);
		tputs(delete_character, 1, ft_putchar);
		cur_pos--;
		(*line)[cur_pos] = '\0';
		if ((*line)[cur_pos + 1] != '\0')
			*line = ft_strjoin_free(*line, *line + cur_pos + 1, 1);
		free(*history_line);
		*history_line = ft_strdup(*line);
	}
	*cursor_pos = cur_pos;
}

void	pressed_key_delete(int *cursor_pos, char **line, char **history_line)
{
	if (*cursor_pos >= 0)
	{
		tputs(delete_character, 1, ft_putchar);
		(*line)[*cursor_pos] = '\0';
		if ((*line)[*cursor_pos + 1] != '\0')
			(*line) = ft_strjoin_free((*line), (*line) + *cursor_pos + 1, 1);
		free(*history_line);
		*history_line = ft_strdup(*line);
	}
}
