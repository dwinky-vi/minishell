/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:25:28 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/06 14:33:26 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_str(char const *s1, char const *s2, int flag)
{
	if (flag == 1)
		free((char *)s1);
	else if (flag == 2)
		free((char *)s2);
	else if (flag == 3)
	{
		free((char *)s1);
		free((char *)s2);
	}
}

char	*ft_strjoin_free(char const *s1, char const *s2, int flag)
{
	char	*s3;
	size_t	s1_len;
	size_t	s2_len;
	size_t	s3_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s3_len = s1_len + s2_len;
	s3 = (char *)ft_calloc(s3_len + 1, sizeof(char));
	if (!s3)
		return (NULL);
	while (*s1)
		*s3++ = *s1++;
	while (*s2)
		*s3++ = *s2++;
	s1 -= s1_len;
	s2 -= s2_len;
	free_str(s1, s2, flag);
	return (s3 - s3_len);
}
