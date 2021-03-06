/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_home_or_end.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 19:06:17 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/29 20:18:40 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	key_home_or_end(char *str, char *line, int *cursor)
{
	if (!ft_strncmp(str, KEY_HOME_FT, ft_strlen(KEY_HOME_FT)))
	{
		while (*cursor > 0)
		{
			(*cursor)--;
			tputs(cursor_left, 1, ft_putchar);
		}
	}
	else if (!ft_strncmp(str, KEY_END_FT, ft_strlen(KEY_END_FT)))
	{
		while ((size_t)(*cursor) < ft_strlen(line))
		{
			(*cursor)++;
			tputs(cursor_right, 1, ft_putchar);
		}
	}
}
