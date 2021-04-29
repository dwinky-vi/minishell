/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 05:20:25 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/29 02:43:03 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	change_pwd_or_oldpwd(t_list *list_env, char *buf, char *str)
{
	char	**pwd;

	pwd = change_env(list_env, str);
	free(*pwd);
	*pwd = ft_strdup(buf);
}

void	check_oldpwd(t_list *list_env, char *buf)
{
	t_envp	*new_env;
	t_list	*new_list;

	if (!get_env_value(list_env, "OLDPWD"))
	{
		new_env = (t_envp *)ft_calloc(1, sizeof(t_envp));
		new_env->name = ft_strdup("OLDPWD");
		new_env->value = ft_strdup(buf);
		new_list = ft_lstnew(new_env);
		ft_lstadd_back(&list_env, new_list);
	}
	else
		change_pwd_or_oldpwd(list_env, buf, "OLDPWD");
}

void	change_dir(t_command *cmd, t_vars *vars)
{
	char	buf[BUFSIZE];
	char	*str;

	getcwd(buf, BUFSIZE);
	if (chdir(cmd->args[1]) == -1)
	{
		str = ft_strjoin(cmd->args[1], ": ");
		str = ft_strjoin_free(str, strerror(errno), 1);
		shell_err(cmd->args, vars->tmp_fd_1, 1, str);
		free(str);
	}
	else
	{
		check_oldpwd(vars->list_env, buf);
		if (get_env_value(vars->list_env, "PWD"))
		{
			getcwd(buf, BUFSIZE);
			change_pwd_or_oldpwd(vars->list_env, buf, "PWD");
		}
	}
}

int	go_old_pwd(t_command *cmd, t_vars *vars)
{
	free(cmd->args[1]);
	cmd->args[1] = ft_strdup(get_env_value(vars->list_env, "OLDPWD"));
	if (!cmd->args[1])
	{
		shell_err(cmd->args, vars->tmp_fd_1, 1, "OLDPWD not set");
		return (0);
	}
	else
		ft_putendl_fd(cmd->args[1], 1);
	return (1);
}

void	make_cd(t_command *cmd, t_vars *vars)
{
	if (!cmd->args[1] || !ft_strncmp(cmd->args[1], "~", 2))
	{
		if (cmd->args[1])
			free(cmd->args[1]);
		cmd->args[1] = ft_strdup(get_env_value(vars->list_env, "HOME"));
		if (!cmd->args[1])
		{
			shell_err(cmd->args, vars->tmp_fd_1, 1, "HOME not set");
			return ;
		}
	}
	else if (!ft_strncmp(cmd->args[1], "-", 2))
	{
		if (!go_old_pwd(cmd, vars))
			return ;
	}
	else if (cmd->args[1][0] == '\0')
		return ;
	change_dir(cmd, vars);
}
