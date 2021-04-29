/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 22:49:15 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/29 04:30:26 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

static void	move_word_left(char *line, int *cursor)
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

static void	move_word_right(char *line, int *cursor)
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

void	move_word(char *str, char *line, int *cursor_pos)
{
	if (!strcmp(str, KEY_LEFT_WORD_FT))
		move_word_left(line, cursor_pos);
	else if (!strcmp(str, KEY_RIGHT_WORD_FT))
		move_word_right(line, cursor_pos);
}
