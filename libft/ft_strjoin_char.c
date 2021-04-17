/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 22:20:23 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/17 22:30:49 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_char(char const *s1, char const ch)
{
	char	*str;
	size_t	k;

	if (s1 == NULL)
		return (NULL);
	str = (char *)ft_calloc(ft_strlen(s1) + sizeof(char) + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	k = 0;
	while (*s1 != '\0')
	{
		*str++ = *s1++;
		k++;
	}
	*str++ = ch;
	*str++ = '\0';
	return (str - k);
}
