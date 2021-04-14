/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_previous_history.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 19:33:56 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/10 19:34:49 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

char	**get_previous_history(int fd, size_t *k)
{
	int		r;
	char	**history;
	char	*line;

	if (fd == -1)
		exit(1); // FIX IT
	history = (char **)ft_calloc(500, sizeof(char *));
	if (history == NULL)
		exit(1); // FIX IT
	while ((r = get_next_line(fd, &line)) >= 0)
	{
		if (*line != '\0')
			history[(*k)++] = line;
		if (r == 0)
			break ;
	}
	free(line);
	return (history);
}
