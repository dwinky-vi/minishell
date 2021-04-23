/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_n_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 22:19:24 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/23 23:40:12 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	make_pipe_or_redir(t_command *cmd, t_vars *vars)
{
	pid_t	pid;
	int		status;

	if (vars->f_pipe == TRUE)
		if (pipe(cmd->fd) == -1)
			return ;
	pid = fork();
	if (pid < 0)
		return ;
	else if (pid == 0)
	{
		dup2(cmd->fd[1], 1);
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		processing(cmd, vars);
		exit(g_code);
	}
	else
	{
		dup2(cmd->fd[0], 0);
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		wait(&status);
		g_code = status / 256;
	}
}
