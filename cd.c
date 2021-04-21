/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 05:20:25 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/21 20:41:02 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	check_oldpwd(t_list *list_env, char *buf)
{
	t_envp	*new_list;
	char	**pwd;
	char	*tmp_pwd;

	if (!get_env_value(list_env, "OLDPWD"))
	{
		new_list = (t_envp *)ft_calloc(1, sizeof(t_envp));
		new_list->name = "OLDPWD";
		new_list->value = ft_strdup(get_env_value(list_env, "PWD"));
		ft_lstadd_back(&list_env, ft_lstnew(new_list));
	}
	else
	{
		pwd = change_env(list_env, "OLDPWD");
		free(*pwd);
		*pwd = ft_strdup(buf);
	}
}

void	change_dir(t_command *cmd, t_list *list_env)
{
	char	**pwd;
	char	buf[BUFSIZE];

	getcwd(buf, BUFSIZE);
	if (chdir(cmd->args[1]) == -1)
	{
		ft_putstr_fd("minishell: ", 1);
		printf("%s: %s: %s\n", cmd->args[0], cmd->args[1], strerror(errno));
		g_code = 1;
	}
	else
	{
		check_oldpwd(list_env, buf);
		if (get_env_value(list_env, "PWD"))
		{
			getcwd(buf, BUFSIZE);
			pwd = change_env(list_env, "PWD");
			free(*pwd);
			*pwd = ft_strdup(buf);
		}
	}
}

void	make_cd(t_command *cmd, t_list *list_env)
{
	if (!cmd->args[1] || !ft_strncmp(cmd->args[1], "~", 2)) // ~ !!!
	{
		cmd->args[1] = ft_strdup(get_env_value(list_env, "HOME"));
		if (!cmd->args[1])
		{
			printf("minishell: %s: %s\n", cmd->args[0], "HOME not set");
			g_code = 1;
			return ;
		}
	}
	else if (cmd->args[1][0] == '-')
	{
		free(cmd->args[1]);
		cmd->args[1] = ft_strdup(get_env_value(list_env, "OLDPWD"));
		if (!cmd->args[1])
		{
			printf("minishell: %s: %s\n", cmd->args[0], "OLDPWD not set");
			g_code = 1;
			return ;
		}
		else
			ft_putendl_fd(cmd->args[1], 1);
	}
	else if (cmd->args[1][0] == '\0')
	{
		free(cmd->args[1]);
		cmd->args[1] = ft_strdup(".");
	}
	change_dir(cmd, list_env);
	return ;
}
