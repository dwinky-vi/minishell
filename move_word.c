/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 22:49:15 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/27 18:07:26 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	move_word(char *str, char *line, int *cursor_pos)
{
	if (!strcmp(str, "\eb"))
		move_word_left(line, cursor_pos);
	else if (!strcmp(str, "\ef"))
		move_word_right(line, cursor_pos);
}

void	move_word_left(char *line, int *cursor)
{
	if (*cursor <= 0)
		return ;
	*cursor -= 1;
	while (!ft_isdigit(line[*cursor]) && !ft_isalpha(line[*cursor]) && \
											*cursor >= 0)
	{
		tputs(cursor_left, 1, ft_putchar);
		(*cursor)--;
	}
	while ((ft_isdigit(line[*cursor]) || ft_isalpha(line[*cursor])) && \
											*cursor >= 0)
	{
		tputs(cursor_left, 1, ft_putchar);
		(*cursor)--;
	}
	*cursor += 1;
}

void	move_word_right(char *line, int *cursor)
{
	size_t	line_len;

	line_len = ft_strlen(line);
	if ((size_t)(*cursor) == line_len)
		return ;
	while (!ft_isdigit(line[*cursor]) && !ft_isalpha(line[*cursor]) && \
											(size_t)(*cursor) < line_len)
	{
		tputs(cursor_right, 1, ft_putchar);
		(*cursor)++;
	}
	while ((ft_isdigit(line[*cursor]) || ft_isalpha(line[*cursor])) && \
											(size_t)(*cursor) < line_len)
	{
		tputs(cursor_right, 1, ft_putchar);
		(*cursor)++;
	}
}
