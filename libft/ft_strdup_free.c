/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 09:57:40 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/23 02:41:23 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_free(const char *s1, int flag)
{
	char	*s1_dup;
	size_t	s1_len;

	if (!s1)
		return (NULL);
	s1_len = ft_strlen(s1);
	s1_dup = ft_calloc(s1_len + 1, sizeof(char));
	if (!s1_dup)
		return (NULL);
	while (*s1)
		*s1_dup++ = *s1++;
	if (flag == 1)
		free((char *)s1 - s1_len);
	return (s1_dup - s1_len);
}
