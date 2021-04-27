/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_in.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 21:17:20 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/27 22:31:57 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

int	ft_find_in(char *str, char find)
{
	size_t	k;

	k = 0;
	while (str[k])
	{
		if (str[k] == find)
			return (TRUE);
		k++;
	}
	return (FALSE);
}
