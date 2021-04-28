/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 19:43:08 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/27 17:30:13 by dwinky           ###   ########.fr       */
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
		exit(1);
	buf2 = buf;
	while (bufsize > 0)
	{
		*buf2 = 0;
		buf2++;
		bufsize--;
	}
	return (buf);
}
