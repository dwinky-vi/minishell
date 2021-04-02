/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 19:10:33 by aquinoa           #+#    #+#             */
/*   Updated: 2021/03/31 21:55:11 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	src_size;

	if (!src)
		return (0);
	src_len = ft_strlen(src);
	src_size = src_len + 1;
	if (src_size < dstsize)
	{
		while (src_size--)
			*dst++ = *src++;
	}
	else if (dstsize != 0)
	{
		while (dstsize-- > 1)
			*dst++ = *src++;
		*dst = '\0';
	}
	return (src_len);
}
