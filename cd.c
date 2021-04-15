/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 05:20:25 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/15 16:53:39 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	check_oldpwd(t_list **list_env, char *buf)
{
	t_envp	*new_list;
	t_list	*tmp_list;
	char	*pwd;

	pwd = get_env_value(list_env, "OLDPWD");
	if (!pwd)
	{
		new_list = (t_envp *)ft_calloc(1, sizeof(t_envp));
		new_list->name = "OLDPWD";
		new_list->value = get_env_value(list_env, "PWD");
		ft_lstadd_back(list_env, ft_lstnew(new_list));
	}
	else
	{
		free(pwd);
		tmp_list = *list_env;
		while (tmp_list)
		{
			if (!ft_strncmp(((t_envp *)tmp_list->content)->name, "OLDPWD", 7))
				((t_envp *)tmp_list->content)->value = ft_strdup(buf);
			tmp_list = tmp_list->next;
		}
	}
}

void	change_dir(t_command *cmd, t_list **list_env)
{
	char	*pwd;
	char	buf[BUFSIZE];
	t_list	*tmp_list;

	getcwd(buf, BUFSIZE);
	if (chdir(cmd->args[1]) == -1)
		printf("bash: %s: %s: %s\n", cmd->args[0], cmd->args[1], strerror(errno));
	else
	{
		check_oldpwd(list_env, buf);
		pwd = get_env_value(list_env, "PWD");
		if (!pwd)
			ft_putendl_fd("!!! no PWD in env !!!", 1);
		else
		{
			free(pwd);
			getcwd(buf, BUFSIZE);
			tmp_list = *list_env;
			while (tmp_list)
			{
				if (!ft_strncmp(((t_envp *)tmp_list->content)->name, "PWD", 4))
					((t_envp *)tmp_list->content)->value = ft_strdup(buf);
				tmp_list = tmp_list->next;
			}
		}
	}
}

void	make_cd(t_command *cmd, t_list **list_env)
{
	if (!cmd->args[1])
	{
		cmd->args[1] = get_env_value(list_env, "HOME");
		if (!cmd->args[1])
		{
			printf("bash: %s: %s\n", cmd->args[0], "HOME not set");
			return ;
		}
	}
	else if (cmd->args[1][0] == '-')
	{
		cmd->args[1] = get_env_value(list_env, "OLDPWD");
		if (!cmd->args[1])
		{
			printf("bash: %s: %s\n", cmd->args[0], "OLDPWD not set");
			return ;
		}
		else
		{
			ft_putendl_fd(cmd->args[1], 1);
			free(cmd->args[1]);
		}
	}
	change_dir(cmd, list_env);
	return ;
}
