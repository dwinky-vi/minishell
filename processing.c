/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 03:26:37 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/06 21:39:56 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	processing(t_command *cmd, t_list *list_env, char **envp)
{
	pid_t		pid;
	int			name_len;

	cmd->fd[0] = 0;
	cmd->fd[1] = 1;
	name_len = ft_strlen(cmd->name);
	if (name_len)
	{
		if (!ft_strncmp(cmd->name, "echo", 5))
			make_echo(cmd);
		else if (!ft_strncmp(cmd->name, "pwd", 4))
			make_pwd(cmd);
		else if (!ft_strncmp(cmd->name, "cd", 3))
			make_cd(cmd);
		else
		{
			pid = fork();
			if (pid == 0)
				make_other(cmd, list_env, envp);
			else
				wait(0);
		}
	}
}
