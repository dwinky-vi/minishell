/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 00:33:15 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/29 01:29:00 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	parent_signal(int param)
{
	if (param == 2)
	{
		ft_putstr_fd("\n", 1);
		g_code = 130;
	}
	else if (param == 3)
	{
		ft_putendl_fd("Quit: 3", 1);
		g_code = 131;
	}
	else
		ft_putstr_fd("error\n", 1);
}

void	child_signal(int param)
{
	if (param == 2)
		g_code = 130;
	else if (param == 3)
		g_code = 131;
	else
		ft_putstr_fd("error\n", 1);
}

int	signal_ctrl_d(char **line, int *cursor, t_history *history)
{
	if ((*line)[0] == '\0')
	{
		ft_putstr_fd("exit\n", 1);
		return (FAILURE_CODE);
	}
	else
		pressed_key_delete(line, cursor, &history->arr[history->current]);
	return (SUCCESS_CODE);
}

void	signal_ctrl_c(char **line, int *cursor, t_history *history)
{
	ft_bzero(*line, ft_strlen(*line));
	ft_putchar_fd('\n', 1);
	print_prompt();
	*cursor = 0;
	g_code = 1;
	if (history->current == history->size)
	{
		free(history->arr[history->current]);
		history->arr[history->current] = NULL;
	}
	history->current = history->size;
}
