/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_up_or_down.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 21:04:49 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/26 21:10:01 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

// void	 pressed_key_up(int *cursor_pos, char **history, int *k)
// {
// 	clear_command_line(*cursor_pos, history[k]);
// 	*cursor_pos = 0;
// 	if (*k > 0)
// 		(*k)--;
// 	free(old_history_line);
// 	old_history_line = ft_strdup(history[*k]);
// 	if (history_size != 0)
// 	{
// 		ft_putstr_fd(history[*k], 1);
// 		free(line);
// 		line = ft_strdup(history[*k]);
// 		*cursor_pos = ft_strlen(history[*k]);
// 	}
// }