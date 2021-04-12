/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:59:23 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/11 00:28:59 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s11;
	unsigned char	*s22;
	int				i;

	s11 = (unsigned char *)s1;
	s22 = (unsigned char *)s2;
	i = 0;
	while ((s11[i] != '\0' || s22[i] != '\0') && n--)
	{
		if (s11[i] == s22[i])
			i++;
		else if (s11[i] > s22[i])
			return (s11[i] - s22[i]);
		else if (s11[i] < s22[i])
			return (s11[i] - s22[i]);
	}
	return (0);
}
