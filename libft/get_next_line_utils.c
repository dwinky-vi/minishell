/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 22:00:00 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/27 13:34:40 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_clear_tail(char **s_tail)
{
	free(*s_tail);
	*s_tail = NULL;
}

char	*ft_strjoin_gnl(char **s1, char *s2)
{
	char	*str;
	size_t	k;

	if (*s1 == NULL || s2 == NULL)
		return (NULL);
	str = (char *)ft_calloc(ft_strlen(*s1) + ft_strlen(s2) + 1, sizeof(char));
	if (str == NULL)
	{
		free(*s1);
		return (NULL);
	}
	k = 0;
	while ((*s1)[k] != '\0')
	{
		*str++ = (*s1)[k];
		k++;
	}
	while (*s2 != '\0' && *s2 != '\n')
	{
		*str++ = *s2++;
		k++;
	}
	free(*s1);
	*s1 = NULL;
	return (str - k);
}
