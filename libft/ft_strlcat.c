/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 01:29:41 by aquinoa           #+#    #+#             */
/*   Updated: 2020/11/13 01:20:36 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	res;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	res = dstlen + srclen;
	if (dstsize <= dstlen)
		return (dstsize + srclen);
	else
	{
		dstsize -= dstlen;
		while (dstsize > 1 && *src)
		{
			dst[dstlen] = *src;
			dstlen++;
			src++;
			dstsize--;
		}
		dst[dstlen] = '\0';
	}
	return (res);
}
