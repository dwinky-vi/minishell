/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 16:33:43 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/22 03:53:59 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	make_pipe(t_command *cmd, t_vars *vars)
{
	pid_t	pid;
	int		status;

	if (pipe(cmd->fd) == -1)
		return ;
	pid = fork();
	if (pid < 0)
		return ;
	else if (pid == 0)
	{
		dup2(cmd->fd[1], 1);
		close(cmd->fd[0]);
		processing(cmd, vars);
		close(cmd->fd[1]);
		exit(g_code);
	}
	else
	{
		dup2(cmd->fd[0], 0);
		close(cmd->fd[1]);
		wait(&status);
		close(cmd->fd[0]);
		g_code = status / 256;
	}
}
