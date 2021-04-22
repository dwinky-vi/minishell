/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 19:33:56 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/21 20:35:08 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

/** права доступа выдаются, как в bash */
/** возвращается индекс, начиная с которого идёт новая история */
int	get_history(char ***history, size_t *k, t_vars *vars)
{
	int		r;
	char	**history_buf;
	char	*line;
	int		fd;
	char	*home_dir;

	home_dir = get_env_value(vars->list_env, "HOME");
	if (home_dir == NULL)
		vars->history_path = ft_strdup(".minishell_history");
	else
		vars->history_path = ft_strjoin(home_dir, "/.minishell_history");
	fd = open(vars->history_path, O_CREAT | O_RDWR | O_APPEND, 0600);
	history_buf = *history;
	if (fd == -1)
		mem_err();
	history_buf = (char **)ft_calloc(500, sizeof(char *));
	if (history_buf == NULL)
		mem_err();
	while ((r = get_next_line(fd, &line)) >= 0)
	{
		if (*line != '\0')
			history_buf[(*k)++] = line;
		else
			free(line);
		if (r == 0)
			break;
	}
    *history = history_buf;
	close(fd);
    return (*k);
}

void	set_history(char **history, int k, t_vars *vars)
{
	int		fd;

	fd = open(vars->history_path, O_CREAT | O_RDWR | O_APPEND, 0600);
	while (history[k])
	{
		ft_putstr_fd(history[k], fd);
		ft_putchar_fd('\n', fd);
		k++;
	}
	close(fd);
	free(vars->history_path);
}