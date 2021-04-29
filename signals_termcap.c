/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_termcap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 03:03:24 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/29 03:28:16 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

static int	signal_ctrl_d(char **line, int *cursor, t_history *history)
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

static void	signal_ctrl_c(char **line, int *cursor, t_history *history)
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

int	is_signal(char *str)
{
	if (!strcmp(str, KEY_CTRL_D_FT))
		return (TRUE);
	else if (!strcmp(str, KEY_CTRL_C_FT))
		return (TRUE);
	else if (!strcmp(str, KEY_CTRL_FS_FT))
		return (TRUE);
	return (FALSE);
}

int	make_signal(char *str, char **line, int *cursor, t_history *history)
{
	if (!strcmp(str, KEY_CTRL_D_FT))
	{
		if (signal_ctrl_d(line, cursor, history) == FAILURE_CODE)
			return (FAILURE_CODE);
	}
	else if (!strcmp(str, KEY_CTRL_C_FT))
		signal_ctrl_c(line, cursor, history);
	return (SUCCESS_CODE);
}
