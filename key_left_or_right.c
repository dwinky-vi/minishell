/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_left_or_right.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 21:00:05 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/29 04:52:09 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	key_left_or_right(char *str, char *line, int *cursor)
{
	int	width_term;

	width_term = tgetnum("columns");
	if (!strcmp(str, KEY_LEFT_FT))
	{
		if (0 < *cursor)
		{
			tputs(cursor_left, 1, ft_putchar);
			(*cursor)--;
		}
	}
	else if (!strcmp(str, KEY_RIGHT_FT))
	{
		if (0 <= *cursor && (size_t)(*cursor) < ft_strlen(line))
		{
			tputs(cursor_right, 1, ft_putchar);
			(*cursor)++;
		}
	}
}
