/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:38:33 by aquinoa           #+#    #+#             */
/*   Updated: 2021/03/31 21:53:07 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_array(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	ft_word_count(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s == c)
			while (*s && *s == c)
				s++;
		else if (*s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

char	**ft_filling(char **res, int i, char const *s, char c)
{
	int			count;
	char const	*s2;

	count = 0;
	s2 = s;
	while (*s && *s != c)
	{
		count++;
		s++;
	}
	res[i] = (char *)ft_calloc(count + 1, sizeof(char));
	if (!res[i])
		ft_free_array(res);
	count = 0;
	while (*s2 && *s2 != c)
	{
		res[i][count] = *s2;
		count++;
		s2++;
	}
	return (res);
}

char	**ft_split(char const *s, char c)
{
	int		word_count;
	char	**res;
	int		i;

	if (!s)
		return (NULL);
	word_count = ft_word_count(s, c);
	res = (char **)ft_calloc(word_count + 1, sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s == c)
			while (*s && *s == c)
				s++;
		else if (*s != c)
		{
			res = ft_filling(res, i, s, c);
			while (*s && *s != c)
				s++;
			i++;
		}
	}
	return (res);
}
