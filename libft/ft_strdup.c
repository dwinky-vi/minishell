/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 09:57:40 by aquinoa           #+#    #+#             */
/*   Updated: 2021/03/31 21:54:05 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s1_dup;
	size_t	s1_len;

	s1_len = ft_strlen(s1);
	s1_dup = ft_calloc(s1_len + 1, sizeof(char));
	if (!s1_dup)
		return (NULL);
	while (*s1)
		*s1_dup++ = *s1++;
	return (s1_dup - s1_len);
}
