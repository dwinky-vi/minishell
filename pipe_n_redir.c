/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_n_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 22:19:24 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/24 04:19:50 by aquinoa          ###   ########.fr       */
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
		// if (vars->f_redir)
		// {
		// 	dup2(cmd->fd[0], 0);)
		// 	dup2(cmd->fd[1], 1);
		// }
		if (vars->f_pipe)
			dup2(cmd->fd[1], 1);
		processing(cmd, vars);
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		exit(g_code);
	}
	else
	{
		if (vars->f_pipe)
			dup2(cmd->fd[0], 0);
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		wait(&status);
		g_code = status / 256;
	}
}
