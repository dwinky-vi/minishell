/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 21:30:45 by aquinoa           #+#    #+#             */
/*   Updated: 2021/03/31 21:49:11 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dst_2;
	unsigned char	*src_2;
	size_t			i;

	dst_2 = (unsigned char *)dst;
	src_2 = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dst_2[i] = src_2[i];
		if (src_2[i] == (unsigned char)c)
		{
			dst_2[i] = src_2[i];
			i++;
			return (dst_2 + i);
		}
		i++;
	}
	return (NULL);
}
