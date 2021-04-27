/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 21:59:43 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/27 17:43:58 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define BUFFER_SIZE 1
/*
** 1 –– всё прочитано, записано и конец файла не был достигнут
** 0 –– линия прочитана, записана, но файл закончился (была последняя строчка)
** -1 –– при любой ошибки: fd –– испорчиный, не смогли аллоцировать память и тд
*/

static int	ft_error(char **str, char *str2)
{
	free(*str);
	*str = NULL;
	free(str2);
	return (-1);
}

static int	check_tail(char **line, char **tail, char **find_end)
{
	char	*cur_ptr;

	cur_ptr = NULL;
	*find_end = ft_strchr(*tail, '\n');
	if ((*tail) != NULL && *find_end)
	{
		*(*find_end) = '\0';
		*line = ft_strdup(*tail);
		cur_ptr = *tail;
		*tail = ft_strdup(*find_end + 1);
		ft_clear_tail(&cur_ptr);
		return (1);
	}
	else if (*tail != NULL)
	{
		*line = ft_strdup(*tail);
		ft_clear_tail(tail);
	}
	else if (*tail == NULL)
		*line = ft_strdup("");
	return (2);
}

static int	set_line(char **array, char **tail, char **find_end)
{
	*find_end = ft_strchr(*array, '\n');
	if (*find_end != NULL)
	{
		*(*find_end) = '\0';
		free(*tail);
		*tail = ft_strdup(*find_end + 1);
	}
	return (1);
}

static int	ft_end_gnl(char **array, char **tail, int r)
{
	free(*array);
	if (r == -1)
	{
		free(*tail);
		return (-1);
	}
	else if (r == 0)
		return (0);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char		*tail = NULL;
	char			*array;
	char			*find_end;
	int				r;

	if (line == NULL || read(fd, NULL, 0) < 0)
		return (-1);
	find_end = NULL;
	r = check_tail(line, &tail, &find_end);
	if (r != 2)
		return (r);
	array = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	r = 1;
	while (!find_end && r > 0)
	{
		r = read(fd, array, BUFFER_SIZE);
		array[r] = '\0';
		if (set_line(&array, &tail, &find_end) == -1)
			return (-1);
		*line = ft_strjoin_gnl(line, array);
	}
	return (ft_end_gnl(&array, &tail, r));
}
