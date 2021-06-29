/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_left_or_right.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 21:00:05 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/29 20:16:39 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	key_left_or_right(char *str, char *line, int *cursor)
{
	int	width_term;

	width_term = tgetnum("columns");
	if (!ft_strncmp(str, KEY_LEFT_FT, ft_strlen(KEY_LEFT_FT)))
	{
		if (0 < *cursor)
		{
			tputs(cursor_left, 1, ft_putchar);
			(*cursor)--;
		}
	}
	else if (!ft_strncmp(str, KEY_RIGHT_FT, ft_strlen(KEY_RIGHT_FT)))
	{
		if (0 <= *cursor && (size_t)(*cursor) < ft_strlen(line))
		{
			tputs(cursor_right, 1, ft_putchar);
			(*cursor)++;
		}
	}
}
