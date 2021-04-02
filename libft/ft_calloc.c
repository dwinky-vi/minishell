/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 19:43:08 by aquinoa           #+#    #+#             */
/*   Updated: 2021/03/31 21:38:33 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*buf;
	char	*buf2;
	size_t	bufsize;

	bufsize = size * count;
	buf = malloc(bufsize);
	if (!buf)
		return (NULL);
	buf2 = buf;
	while (bufsize > 0)
	{
		*buf2 = 0;
		buf2++;
		bufsize--;
	}
	return (buf);
}
