/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:57:11 by aquinoa           #+#    #+#             */
/*   Updated: 2021/03/31 21:50:38 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dst_2;
	const unsigned char	*src_2;

	if (!dst && !src)
		return (NULL);
	dst_2 = dst;
	src_2 = src;
	if ((size_t)(src - dst) >= len)
		while (len--)
			dst_2[len] = src_2[len];
	else
		while (len--)
			*dst_2++ = *src_2++;
	return (dst);
}
