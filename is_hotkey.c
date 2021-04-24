/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_hotkey.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 18:37:05 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/24 21:14:03 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

int	is_hotkey(char *str)
{
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
