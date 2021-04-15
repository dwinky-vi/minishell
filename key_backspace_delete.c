/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_backspace_delete.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 19:14:34 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/10 19:22:27 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	pressed_key_backspace(int *cursor_pos, char **line)
{
	if (*cursor_pos > 0)
	{
		(*cursor_pos)--;
		tputs(cursor_left, 1, ft_putchar);
		tputs(delete_character, 1, ft_putchar);
		(*line)[*cursor_pos] = '\0';
		if ((*line)[*cursor_pos + 1] != '\0')
			*line = ft_strjoin_free(*line, *line + *cursor_pos + 1, 1);
	}
}

void	pressed_key_delete(int *cursor_pos, char **line)
{
	if (*cursor_pos >= 0)
	{
		tputs(delete_character, 1, ft_putchar);
		(*line)[*cursor_pos] = '\0';
		if ((*line)[*cursor_pos + 1] != '\0')
			(*line) = ft_strjoin_free((*line), (*line) + *cursor_pos + 1, 1);
	}
}
