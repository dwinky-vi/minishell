/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 19:33:56 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/28 16:49:20 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	set_history_path(t_vars *vars)
{
	char	*home_dir;

	home_dir = get_env_value(vars->list_env, "HOME");
	if (home_dir == NULL)
		vars->history_path = ft_strdup(".minishell_history");
	else
		vars->history_path = ft_strjoin(home_dir, "/.minishell_history");
}

/** permissions are given as in bash */
/** returns the index from which the new history starts */
void	get_history(t_history *history, t_vars *vars)
{
	int		r;
	char	**history_buf;
	char	*line;
	int		fd;

	history->current = 0;
	set_history_path(vars);
	fd = open(vars->history_path, O_CREAT | O_RDWR | O_APPEND, 0600);
	if (fd == -1)
		exit(1);
	history_buf = (char **)ft_calloc(1024, sizeof(char *));
	r = get_next_line(fd, &line);
	while (r >= 0)
	{
		if (*line != '\0')
			history_buf[(history->current)++] = line;
		else
			free(line);
		if (r == 0)
			break ;
		r = get_next_line(fd, &line);
	}
	history->arr = history_buf;
	close(fd);
	history->start_local_history = history->current;
}

void	set_history(t_history *history, t_vars *vars)
{
	int		fd;
	size_t	k;

	fd = open(vars->history_path, O_CREAT | O_RDWR | O_APPEND, 0600);
	if (fd == -1)
		exit(1);
	k = history->start_local_history;
	while (history->arr[k])
	{
		ft_putendl_fd(history->arr[k], fd);
		k++;
	}
	close(fd);
	free(vars->history_path);
}
