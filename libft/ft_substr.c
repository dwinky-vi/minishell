/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:16:06 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/01 03:21:36 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*new_str(unsigned int start, size_t *len, size_t str_len)
{
	char	*str;

	if (*len > (str_len - start))
		*len = str_len - start;
	str = (char *)malloc(*len + 1);
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
		sub_str = (char *)malloc(1);
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
