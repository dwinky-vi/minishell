/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_n_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 22:19:24 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/26 17:05:32 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	make_pipe_or_redir(t_command *cmd, t_vars *vars)
{
	pid_t	pid;
	int		status;

	if (vars->f_redir)
	{
		close(cmd->fd[1]);
		close(cmd->fd[0]);
	}
	if (vars->f_pipe == TRUE)
		if (pipe(cmd->fd) == -1)
			return ;
	pid = fork();
	if (pid < 0)
		return ;
	else if (pid == 0)
	{
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
		signal(SIGINT, &for_signal); // Это ловит ctrl-C.  Код сигнала –– 2
		signal(SIGQUIT, &for_signal); // Это ловит ctrl-\. Код сигнала –– 3
		return_term(&vars->term);
		wait(&status);
		init_term(&vars->term, get_term_name(vars->list_env));
		g_code = status / 256;
	}
}
