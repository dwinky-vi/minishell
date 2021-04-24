/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 22:49:15 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/24 22:49:31 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	move_word_left(char *line, int *cursor_pos)
{
	if (*cursor_pos == 0)
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

		/** не работает */
void	move_word_right(char *line, int *cursor_pos)
{
	size_t line_len;

	line_len = ft_strlen(line);
	if (*cursor_pos == line_len)
		return ;
	*cursor_pos -= 1;
	while (!ft_isdigit(line[*cursor_pos]) && !ft_isalpha(line[*cursor_pos]) && *cursor_pos <= line_len)
	{
		tputs(cursor_right, 1, ft_putchar);
		(*cursor_pos)++;
	}
	while ((ft_isdigit(line[*cursor_pos]) || ft_isalpha(line[*cursor_pos])) && *cursor_pos <= line_len)
	{
		tputs(cursor_right, 1, ft_putchar);
		(*cursor_pos)++;
	}
	*cursor_pos += 1;

}
