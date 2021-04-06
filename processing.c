/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 03:26:37 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/06 18:29:21 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	processing(t_command *cmd, t_list *envp, char **env)
{
	pid_t		pid;

	// cmd = ft_calloc(sizeof(t_command), 1);
	// init_command(cmd, ac, av, envp);
	if (!ft_strncmp(cmd->name, "echo", ft_strlen(cmd->name)))
		make_echo(cmd);
	else if (!ft_strncmp(cmd->name, "pwd", ft_strlen(cmd->name)))
		make_pwd(cmd);
	else if (!ft_strncmp(cmd->name, "cd", ft_strlen(cmd->name)))
		make_cd(cmd);
	else
	{
		pid = fork();
		if (pid == 0)
			make_other(cmd, envp, env);
		else
			wait(0);
	}
}
