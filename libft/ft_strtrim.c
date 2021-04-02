/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 18:33:03 by aquinoa           #+#    #+#             */
/*   Updated: 2021/03/31 22:03:36 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_copy(int begin, size_t end, const char *s1)
{
	char	*s2;
	size_t	s2_len;

	s2_len = end - begin + 1;
	s2 = (char *)ft_calloc(s2_len + 1, sizeof(char));
	if (!s2)
		return (NULL);
	ft_memcpy(s2, s1 + begin, s2_len);
	return (s2);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	size_t	s1_len;

	if (!s1 || !set)
		return (0);
	i = 0;
	s1_len = ft_strlen(s1);
	while (s1[i] != '\0')
	{
		if (ft_strchr(set, s1[i]) != 0)
			i++;
		else
			break ;
	}
	if (s1[i] == '\0')
		return ((char *)ft_calloc(1, sizeof(char)));
	while (s1[s1_len - 1] != '\0')
	{
		if (ft_strrchr(set, s1[s1_len]) != 0)
			s1_len--;
		else
			break ;
	}
	return (ft_copy(i, s1_len, s1));
}
