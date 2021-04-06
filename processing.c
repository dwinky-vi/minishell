/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 03:26:37 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/06 20:46:05 by aquinoa          ###   ########.fr       */
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
		if (!ft_strncmp(cmd->name, "echo", name_len))
			make_echo(cmd);
		else if (!ft_strncmp(cmd->name, "pwd", name_len))
			make_pwd(cmd);
		else if (!ft_strncmp(cmd->name, "cd", name_len))
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
