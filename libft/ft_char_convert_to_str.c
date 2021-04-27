/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_convert_to_str.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 22:49:57 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/27 15:22:07 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** This function allocate memory for str */
char	*char_convert_to_str(char ch)
{
	char	*str;

	str = (char *)ft_calloc(2, sizeof(char));
	if (str == NULL)
		return (NULL);
	str[0] = ch;
	return (str);
}
