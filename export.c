/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 21:17:25 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/28 18:15:20 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	add_varible(t_command *cmd, t_vars *vars, int i, int equal)
{
	char	*key;
	char	*value;

	key = ft_substr(cmd->args[i], 0, equal);
	if (!key)
		mem_err();
	if (!check_key(cmd, key, i, vars->tmp_fd_1))
	{
		free(key);
		return ;
	}
	if (vars->export)
		check_exp(vars, key);
	value = ft_substr(cmd->args[i], ++equal, BUFSIZE);
	if (!value)
		mem_err();
	adding_variable(cmd->args[i], vars, key, value);
	free(key);
	free(value);
}

void	search_variable(t_command *cmd, t_vars *vars, int i)
{
	t_list	*new_exp_list;

	if (!searching_variable(cmd, vars, i))
	{
		new_exp_list = ft_lstnew(ft_strdup(cmd->args[i]));
		if (!new_exp_list)
			mem_err();
		ft_lstadd_back(&vars->export, new_exp_list);
	}
}

void	making_export(t_command *cmd, t_vars *vars)
{
	int		i;
	int		equal;

	i = 0;
	while (cmd->args[++i])
	{
		if (cmd->args[i][0] == '=')
		{
			env_err(cmd, i, vars->tmp_fd_1);
			continue ;
		}
		equal = equal_sign(cmd->args[i]);
		if (!equal)
		{
			if (!check_key(cmd, cmd->args[i], i, vars->tmp_fd_1))
				continue ;
			search_variable(cmd, vars, i);
		}
		else
			add_varible(cmd, vars, i, equal);
	}
}

void	simple_export(t_vars *vars)
{
	int		i;
	char	**env;

	env = sort_env(vars->list_env, 1);
	i = -1;
	while (env[++i])
		ft_putendl_fd(env[i], 1);
	ft_free_array(env);
	env = sort_env(vars->export, 0);
	i = -1;
	while (env[++i])
		ft_putendl_fd(env[i], 1);
	ft_free_array(env);
}

void	make_export(t_command *cmd, t_vars *vars)
{
	if (!cmd->args[1])
		simple_export(vars);
	else
		making_export(cmd, vars);
	new_envp(vars);
}
