/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 02:25:20 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/29 20:12:23 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

int	is_bonus_key(char *str)
{
	if (!ft_strncmp(str, KEY_LEFT_FT, ft_strlen(KEY_LEFT_FT)) || \
		!ft_strncmp(str, KEY_RIGHT_FT, ft_strlen(KEY_RIGHT_FT)))
		return (TRUE);
	else if (!ft_strncmp(str, KEY_HOME_FT, ft_strlen(KEY_HOME_FT)) || \
			!ft_strncmp(str, KEY_END_FT, ft_strlen(KEY_END_FT)))
		return (TRUE);
	else if (!ft_strncmp(str, KEY_LEFT_WORD_FT, ft_strlen(KEY_LEFT_WORD_FT)) || \
			!ft_strncmp(str, KEY_RIGHT_WORD_FT, ft_strlen(KEY_RIGHT_WORD_FT)))
		return (TRUE);
	else if (!ft_strncmp(str, KEY_TAB_FT, 1) || is_hotkey(str))
		return (TRUE);
	else
		return (FALSE);
}

void	make_bonus(char *str, char *line, int *cursor_pos)
{
	if (!ft_strncmp(str, KEY_LEFT_FT, ft_strlen(KEY_LEFT_FT)) || \
		!ft_strncmp(str, KEY_RIGHT_FT, ft_strlen(KEY_RIGHT_FT)))
		key_left_or_right(str, line, cursor_pos);
	else if (!ft_strncmp(str, KEY_HOME_FT, ft_strlen(KEY_HOME_FT)) || \
			!ft_strncmp(str, KEY_END_FT, ft_strlen(KEY_END_FT)))
		key_home_or_end(str, line, cursor_pos);
	else if (!ft_strncmp(str, KEY_LEFT_WORD_FT, ft_strlen(KEY_LEFT_WORD_FT)) || \
			!ft_strncmp(str, KEY_RIGHT_WORD_FT, ft_strlen(KEY_RIGHT_WORD_FT)))
		move_word(str, line, cursor_pos);
	else if (!ft_strncmp(str, KEY_TAB_FT, 1) || is_hotkey(str))
		;
}
