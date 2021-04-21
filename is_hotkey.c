/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_hotkey.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 18:37:05 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/21 18:58:41 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

/**
 * shift + ↑⬆︎⬇︎⬅︎➡⬅︎➡️⬅️⬆️➡️➡️➡️➡️⬅️🔼⏩⬇️
 * shift + ⬆️   –– ;2A
 * shift + ⬇️   –– ;2B
 * shift + <-   –– ;2D
 * shift + ->   –– ;2C
 * ******************
 * option + ⬆️   –– ;3A
 * option + ⬇️   –– ;3B
 * ******************
 * shift + option + ⬆️   –– ;4A
 * shift + option + ⬇️   –– ;4B
 * shift + option + ->   –– ;4C
 * shift + option + <-   –– ;4D
 * ******************
 * shift + control + ⬆️   –– ;6A
 * shift + control + ⬇️   –– ;6B
 * shift + control + ->   –– ;6C
 * shift + control + <-   –– ;6D
 * ******************
 * control + option + ⬆️   –– ;7A
 * control + option + ⬇️   –– ;7B
 * control + option + ->   –– ;7C
 * control + option + <-   –– ;7D
 * ******************
 * shift + control + option + ⬆️   –– ;8A
 * shift + control + option + ⬇️   –– ;8B
 * shift + control + option + ->   –– ;8C
 * shift + control + option + <-   –– ;8D
 * ******************
 */

int	is_hotkey(char *str)
{
	if (!ft_strncmp(str, "\t", 1))
		return (1);
	if (!ft_strncmp(str, "\e[1;", 4))
		str += 4;
	else
		return (0);
	if (!ft_strncmp(str, "3A", 2) || !ft_strncmp(str, "3B", 2) || \
		!ft_strncmp(str, "2A", 2) || !ft_strncmp(str, "2B", 2) || \
		!ft_strncmp(str, "2C", 2) || !ft_strncmp(str, "2D", 2) || \
		!ft_strncmp(str, "4A", 2) || !ft_strncmp(str, "4B", 2) || \
		!ft_strncmp(str, "4C", 2) || !ft_strncmp(str, "4D", 2) || \
		!ft_strncmp(str, "6A", 2) || !ft_strncmp(str, "6B", 2) || \
		!ft_strncmp(str, "6C", 2) || !ft_strncmp(str, "6D", 2) || \
		!ft_strncmp(str, "7A", 2) || !ft_strncmp(str, "7B", 2) || \
		!ft_strncmp(str, "7C", 2) || !ft_strncmp(str, "7D", 2) || \
		!ft_strncmp(str, "8A", 2) || !ft_strncmp(str, "8B", 2) || \
		!ft_strncmp(str, "8C", 2) || !ft_strncmp(str, "8D", 2))
		return (1);
	return (0);
}

	// if (!strcmp(str, "\t") || !strcmp(str, "\e[1;3A") || !strcmp(str, "\e[1;3B") || \
	// 	!strcmp(str, "\e[1;2A") || !strcmp(str, "\e[1;2B") || !strcmp(str, "\e[1;2C") || !strcmp(str, "\e[1;2D") || \
	// 	!strcmp(str, "\e[1;4A") || !strcmp(str, "\e[1;4B") || !strcmp(str, "\e[1;4C") || !strcmp(str, "\e[1;4D") || \
	// 	!strcmp(str, "\e[1;6A") || !strcmp(str, "\e[1;6B") || !strcmp(str, "\e[1;6C") || !strcmp(str, "\e[1;6D") || \
	// 	!strcmp(str, "\e[1;7A") || !strcmp(str, "\e[1;7B") || !strcmp(str, "\e[1;7C") || !strcmp(str, "\e[1;7D") || \
	// 	!strcmp(str, "\e[1;8A") || !strcmp(str, "\e[1;8B") || !strcmp(str, "\e[1;8C") || !strcmp(str, "\e[1;8D"))
