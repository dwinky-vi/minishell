/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_home_end.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 19:06:17 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/17 19:55:04 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	pressed_key_home(int *cursor_pos, char **line)
{
	while (*cursor_pos > 0 )
	{
		(*cursor_pos)--;
		tputs(cursor_left, 1, ft_putchar);
	}
}

void	pressed_key_end(int *cursor_pos, char **line)
{
	while (*cursor_pos < ft_strlen(*line))
	{
		(*cursor_pos)++;
		tputs(cursor_right, 1, ft_putchar);
	}
}
