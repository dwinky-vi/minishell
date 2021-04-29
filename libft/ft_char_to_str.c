/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_to_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 22:49:57 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/29 04:31:59 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** This function allocate memory for str */
char	*char_to_str(char ch)
{
	char	*str;

	str = (char *)ft_calloc(2, sizeof(char));
	if (str == NULL)
		return (NULL);
	str[0] = ch;
	return (str);
}
