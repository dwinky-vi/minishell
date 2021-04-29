/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 02:25:20 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/29 02:30:49 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

int	is_bonus_key(char *str)
{
	if (!strcmp(str, KEY_LEFT_FT) || !strcmp(str, KEY_RIGHT_FT))
		return (TRUE);
	else if (!strcmp(str, KEY_HOME_FT) || !strcmp(str, KEY_END_FT))
		return (TRUE);
	else if (!strcmp(str, KEY_LEFT_WORD_FT) || !strcmp(str, KEY_RIGHT_WORD_FT))
		return (TRUE);
	else if (!ft_strncmp(str, KEY_TAB_FT, 1) || is_hotkey(str))
		return (TRUE);
	else
		return (FALSE);
}

void	make_bonus(char *str, char *line, int *cursor_pos)
{
	if (!strcmp(str, KEY_LEFT_FT) || !strcmp(str, KEY_RIGHT_FT))
		key_left_or_right(str, line, cursor_pos);
	else if (!strcmp(str, KEY_HOME_FT) || !strcmp(str, KEY_END_FT))
		key_home_or_end(str, line, cursor_pos);
	else if (!strcmp(str, KEY_LEFT_WORD_FT) || !strcmp(str, KEY_RIGHT_WORD_FT))
		move_word(str, line, cursor_pos);
	else if (!ft_strncmp(str, KEY_TAB_FT, 1) || is_hotkey(str))
		;
}
