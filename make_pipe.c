/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 16:33:43 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/20 03:02:02 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	make_pipe(t_command *cmd, t_vars *vars)
{
	pid_t	pid;
	int		status;

	if (pipe(cmd->fd) == -1)
	{
		ft_putendl_fd("Pipe error!", 1);
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		ft_putendl_fd("Fork error!", 1);
		return ;
	}
	else if (pid == 0)
	{
		dup2(cmd->fd[1], STDOUT_FILENO);
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		processing(cmd, vars);
	}
	else
	{
		dup2(cmd->fd[0], STDIN_FILENO);
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		wait(&status);
		g_code = status / 256;
	}
}
