/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_left_or_right.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 21:00:05 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/29 02:21:12 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

			/** repeat command quantity times */
static void	repeat_command(char *command, int quantity)
{
	int	k;

	k = 0;
	while (k < quantity)
	{
		tputs(command, 1, ft_putchar);
		k++;
	}
}

void	key_left_or_right(char *str, char *line, int *cursor_pos)
{
	int	width_term;

	width_term = tgetnum("columns");
	if (!strcmp(str, "\e[D"))
	{
		if ((*cursor_pos + WIDTH_PROMT) >= width_term && (*cursor_pos + WIDTH_PROMT) % width_term == 0)
		{
			tputs(cursor_up, 1, ft_putchar);
			repeat_command(cursor_right, width_term);
			(*cursor_pos)--;
		}
		else if (0 < *cursor_pos)
		{
			tputs(cursor_left, 1, ft_putchar);
			(*cursor_pos)--;
		}
	}
	else if (!strcmp(str, "\e[C"))
	{
		if ((size_t)(*cursor_pos) < ft_strlen(line) && (*cursor_pos + WIDTH_PROMT - 1) == width_term)
		{
			tputs(cursor_down, 1, ft_putchar);
			repeat_command(cursor_left, width_term);
			(*cursor_pos)++;
		}
		else if (0 <= *cursor_pos && (size_t)(*cursor_pos) < ft_strlen(line))
		{
			tputs(cursor_right, 1, ft_putchar);
			(*cursor_pos)++;
		}
	}
}
