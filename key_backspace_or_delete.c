/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_backspace_or_delete.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 19:14:34 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/29 20:18:10 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

static void	pressed_key_backspace(char **line, int *cursor, char **history_line)
{
	int	cur_pos;

	cur_pos = *cursor;
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
	*cursor = cur_pos;
}

void	pressed_key_delete(char **line, int *cursor, char **history_line)
{
	if (*cursor >= 0)
	{
		tputs(delete_character, 1, ft_putchar);
		(*line)[*cursor] = '\0';
		if ((*line)[*cursor + 1] != '\0')
			(*line) = ft_strjoin_free((*line), (*line) + *cursor + 1, 1);
		free(*history_line);
		*history_line = ft_strdup(*line);
	}
}

void	key_backspace_or_delete(char *str, char **line, int *cursor, \
														char **history_line)
{
	if (!ft_strncmp(str, "\177", 1))
		pressed_key_backspace(line, cursor, history_line);
	else if (!ft_strncmp(str, "\e[3~", 4))
		pressed_key_delete(line, cursor, history_line);
}
