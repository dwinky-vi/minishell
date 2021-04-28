/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:16:06 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/27 16:58:23 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*new_str(unsigned int start, size_t *len, size_t str_len)
{
	char	*str;

	if (*len > (str_len - start))
		*len = str_len - start;
	str = (char *)ft_calloc(*len + 1, sizeof(char));
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char		*sub_str;
	size_t		str_len;
	size_t		sub_str_len;

	if (!str)
		return (NULL);
	str_len = ft_strlen(str);
	sub_str_len = 0;
	if (start >= str_len)
	{
		sub_str = (char *)ft_calloc(1, sizeof(char));
		if (!sub_str)
			return (NULL);
	}
	else
	{
		sub_str = new_str(start, &len, str_len);
		if (!sub_str)
			return (NULL);
		sub_str_len = len;
		while (len--)
			*sub_str++ = str[start++];
	}
	*sub_str = '\0';
	return (sub_str - sub_str_len);
}
