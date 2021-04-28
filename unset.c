/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 19:15:40 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/28 13:08:40 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	del(void *env)
{
	free(((t_envp *)env)->name);
	free(((t_envp *)env)->value);
	free(env);
}

void	delet_list(t_list **list_env)
{
	t_list	*previous;
	t_list	*del_list;
	t_list	*following;

	previous = *list_env;
	del_list = (*list_env)->next;
	following = del_list->next;
	ft_lstdelone(del_list, &del);
	previous->next = following;
}

int	check_exp_list(t_command *cmd, t_vars *vars, int i)
{
	t_list	*tmp_exp;

	tmp_exp = vars->export;
	if (!ft_strncmp(tmp_exp->content, cmd->args[i], BUFSIZE))
	{
		vars->export = vars->export->next;
		free(tmp_exp->content);
		free(tmp_exp);
		return (0);
	}
	tmp_exp = vars->export;
	while (tmp_exp->next)
	{
		if (!ft_strncmp(tmp_exp->next->content, cmd->args[i], BUFSIZE))
		{
			del_exp(tmp_exp);
			break ;
		}
		tmp_exp = tmp_exp->next;
	}
	return (1);
}

int	check_env_list(t_command *cmd, t_vars *vars, int i)
{
	t_list	*tmp_env;

	tmp_env = vars->list_env;
	if (!ft_strncmp(((t_envp *)tmp_env->content)->name, cmd->args[i], BUFSIZE))
	{
		tmp_env = (vars->list_env)->next;
		free(((t_envp *)(vars->list_env)->content)->name);
		free(((t_envp *)(vars->list_env)->content)->value);
		free((t_envp *)(vars->list_env)->content);
		*vars->list_env = *tmp_env;
		free(tmp_env);
		return (0);
	}
	while (tmp_env->next)
	{
		if (!ft_strncmp(((t_envp *)tmp_env->next->content)->name, \
											cmd->args[i], BUFSIZE))
		{
			delet_list(&tmp_env);
			break ;
		}
		tmp_env = tmp_env->next;
	}
	return (1);
}

void	make_unset(t_command *cmd, t_vars *vars)
{
	int		i;

	i = 0;
	while (cmd->args[++i])
	{
		if (!ft_strncmp(cmd->args[i], "_", 2))
			continue ;
		if (!check_key(cmd, cmd->args[i], i, vars->tmp_fd_1))
			continue ;
		if (!check_env_list(cmd, vars, i))
			continue ;
		if (vars->export)
		{
			if (!check_exp_list(cmd, vars, i))
				continue ;
		}
	}
	new_envp(vars);
}
