/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 22:19:24 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/28 10:47:06 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	write_in_pipe(t_command *cmd, t_vars *vars)
{
	dup2(cmd->fd[1], 1);
	processing(cmd, vars);
	close(cmd->fd[0]);
	close(cmd->fd[1]);
	exit(g_code);
}

void	read_from_pipe(t_command *cmd, t_vars *vars)
{
	int		status;

	dup2(cmd->fd[0], 0);
	close(cmd->fd[0]);
	close(cmd->fd[1]);
	signal(SIGINT, &parent_signal);
	signal(SIGQUIT, &parent_signal);
	return_term(&vars->term);
	wait(&status);
	init_term(&vars->term, get_term_name(vars->list_env));
	g_code = status / 256;
}

void	make_pipe(t_command *cmd, t_vars *vars)
{
	pid_t	pid;

	if (vars->f_redir_0 || vars->f_redir_1)
	{
		close(cmd->fd[1]);
		close(cmd->fd[0]);
	}
	if (pipe(cmd->fd) == -1)
		return ;
	pid = fork();
	if (pid < 0)
		return ;
	else if (pid == 0)
		write_in_pipe(cmd, vars);
	else
		read_from_pipe(cmd, vars);
}
