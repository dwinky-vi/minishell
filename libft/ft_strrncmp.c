/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrncmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 23:02:09 by aquinoa           #+#    #+#             */
/*   Updated: 2021/03/31 21:58:37 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strrncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s11;
	unsigned char	*s22;
	size_t			len1;
	size_t			len2;

	s11 = (unsigned char *)s1;
	s22 = (unsigned char *)s2;
	len1 = ft_strlen(s1) - 1;
	len2 = ft_strlen(s2) - 1;
	while (s11[len1] != '\0' && s22[len2] != '\0' && n--)
	{
		if (s11[len1] == s22[len2])
		{
			len1--;
			len2--;
		}
		else if (s11[len1] > s22[len2])
			return (1);
		else if (s11[len1] < s22[len2])
			return (-1);
	}
	return (0);
}
