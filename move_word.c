/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 22:49:15 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/25 01:40:19 by dwinky           ###   ########.fr       */
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

void	move_word_left(char *line, int *cursor_pos)
{
	if (*cursor_pos <= 0)
		return ;
	*cursor_pos -= 1;
	while (!ft_isdigit(line[*cursor_pos]) && !ft_isalpha(line[*cursor_pos]) && *cursor_pos >= 0)
	{
		tputs(cursor_left, 1, ft_putchar);
		(*cursor_pos)--;
	}
	while ((ft_isdigit(line[*cursor_pos]) || ft_isalpha(line[*cursor_pos])) && *cursor_pos >= 0)
	{
		tputs(cursor_left, 1, ft_putchar);
		(*cursor_pos)--;
	}
	*cursor_pos += 1;
}

void	move_word_right(char *line, int *cursor_pos)
{
	size_t	line_len;

	line_len = ft_strlen(line);
	if (*cursor_pos == line_len)
		return ;
	while (!ft_isdigit(line[*cursor_pos]) && !ft_isalpha(line[*cursor_pos]) && *cursor_pos < line_len)
	{
		tputs(cursor_right, 1, ft_putchar);
		(*cursor_pos)++;
	}
	while ((ft_isdigit(line[*cursor_pos]) || ft_isalpha(line[*cursor_pos])) && *cursor_pos < line_len)
	{
		tputs(cursor_right, 1, ft_putchar);
		(*cursor_pos)++;
	}
}