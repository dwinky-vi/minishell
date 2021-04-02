/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:58:14 by aquinoa           #+#    #+#             */
/*   Updated: 2020/11/12 16:54:36 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	s_len;
	int		i;

	if (!s)
		return ;
	i = 0;
	s_len = ft_strlen(s);
	while (s_len)
	{
		write(fd, &s[i], 1);
		i++;
		s_len--;
	}
}
