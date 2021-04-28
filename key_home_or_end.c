/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_home_or_end.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 19:06:17 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/27 18:03:22 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	key_home_or_end(char *str, char *line, int *cursor_pos)
{
	if (!strcmp(str, "\e[H"))
	{
		while (*cursor_pos > 0)
		{
			(*cursor_pos)--;
			tputs(cursor_left, 1, ft_putchar);
		}
	}
	else if (!strcmp(str, "\e[F"))
	{
		while ((size_t)(*cursor_pos) < ft_strlen(line))
		{
			(*cursor_pos)++;
			tputs(cursor_right, 1, ft_putchar);
		}
	}
}
