/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 21:59:43 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/06 20:17:12 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define BUFFER_SIZE 32
/*
** 1 –– всё прочитано, записано и конец файла не был достигнут
** 0 –– линия прочитана, записана, но файл закончился (была последняя строчка)
** -1 –– при любой ошибки: fd –– испорчиный, не смогли аллоцировать память и тд
*/

static int		ft_error(char **str, char *str2)
{
	free(*str);
	*str = NULL;
	free(str2);
	return (-1);
}

static char		*ft_strjoin_to_new_line_and_free(char **s1, char *s2)
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

static int		check_tail(char **line, char **tail, char **find_end)
{
	char	*cur_ptr;

	cur_ptr = NULL;
	if ((*tail) != NULL && (*find_end = ft_strchr(*tail, '\n')))
	{
		*(*find_end) = '\0';
		if (!(*line = ft_strdup(*tail)))
			return (ft_error(tail, NULL));
		cur_ptr = *tail;
		if (!(*tail = ft_strdup(*find_end + 1)))
			return (ft_error(&cur_ptr, NULL));
		ft_clear_tail(&cur_ptr);
		return (1);
	}
	else if (*tail != NULL)
	{
		if ((*line = ft_strdup(*tail)) == NULL)
			return (ft_error(tail, NULL));
		ft_clear_tail(tail);
	}
	else if (*tail == NULL)
		if ((*line = ft_strdup("")) == NULL)
			return (ft_error(tail, NULL));
	return (2);
}

static int		set_line(char **array, char **tail, char **find_end)
{
	if ((*find_end = ft_strchr(*array, '\n')) != NULL)
	{
		*(*find_end) = '\0';
		free(*tail);
		if (!(*tail = ft_strdup(*find_end + 1)))
			return (ft_error(tail, *array));
	}
	return (1);
}

int				get_next_line(int fd, char **line)
{
	static	char	*tail = NULL;
	char			*array;
	char			*find_end;
	int				r;

	if (line == NULL || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
		return (-1);
	find_end = NULL;
	if ((r = check_tail(line, &tail, &find_end)) != 2)
		return (r);
	if (!(array = (char *)malloc(BUFFER_SIZE + 1)))
		return (ft_error(&tail, NULL));
	while (!find_end && (r = read(fd, array, BUFFER_SIZE)) > 0)
	{
		array[r] = '\0';
		if (set_line(&array, &tail, &find_end) == -1)
			return (-1);
		if ((*line = ft_strjoin_to_new_line_and_free(line, array)) == NULL)
			return (ft_error(&tail, array));
	}
	free(array);
	if (r == -1)
		return (ft_error(&tail, NULL));
	return (r == 0 ? 0 : 1);
}
