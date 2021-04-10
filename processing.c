/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 03:26:37 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/10 20:31:48 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void mem_err()
{
	ft_putendl_fd("Memory error!" , 1);
	exit(0);
}

char	*get_env_value(t_list **list_env, char *key)
{
	int		key_len;
	t_list	*tmp_list;

	tmp_list = *list_env;
	key_len = ft_strlen(key) + 1;
	while (tmp_list)
	{
		if (!ft_strncmp(((t_envp *)tmp_list->content)->name, key, key_len))
			break ;
		tmp_list = tmp_list->next;
	}
	if (!tmp_list)
		return (NULL);
	return (((t_envp *)tmp_list->content)->value);
}

void	processing(t_command *cmd, t_list **list_env, char **envp)
{
	pid_t		pid;
	int			name_len;

	cmd->fd[0] = 0;
	cmd->fd[1] = 1;
	name_len = ft_strlen(cmd->name) + 1;
	if (name_len - 1)
	{
		if (!ft_strncmp(cmd->name, "echo", name_len))
			make_echo(cmd);
		else if (!ft_strncmp(cmd->name, "pwd", name_len))
			make_pwd(cmd);
		else if (!ft_strncmp(cmd->name, "cd", name_len))
			make_cd(cmd, list_env);
		else if (!ft_strncmp(cmd->name, "env", name_len))
			make_env(cmd, list_env);
		else if (!ft_strncmp(cmd->name, "unset", name_len))
			make_unset(cmd, list_env);
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
