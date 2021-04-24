/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_left_right.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 21:00:05 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/24 21:13:39 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	key_left_or_right(int *cursor_pos, char *str, size_t line_len)
{
	if (!strcmp(str, "\e[D"))
	{
		if (0 < *cursor_pos)
		{
			tputs(cursor_left, 1, ft_putchar);
			(*cursor_pos)--;
		}
	}
	else if (!strcmp(str, "\e[C"))
	{
		if (0 <= *cursor_pos && *cursor_pos < line_len)
		{
			tputs(cursor_right, 1, ft_putchar);
			(*cursor_pos)++;
		}
	}
}
