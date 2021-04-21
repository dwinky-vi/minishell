/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 19:15:40 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/20 02:59:35 by aquinoa          ###   ########.fr       */
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

void	make_unset(t_command *cmd, t_vars *vars)
{
	t_list	*tmp_env;
	int		i;

	i = 0;
	while (cmd->args[++i])
	{
		if (!ft_isalpha(cmd->args[i][0]) && ft_strncmp(cmd->args[i], "_", 2)) // _  !!!
			env_err(cmd, i);
		tmp_env = vars->list_env;
		if (!ft_strncmp(((t_envp *)tmp_env->content)->name, cmd->args[i], 99))
		{
			tmp_env = (vars->list_env)->next;
			free(((t_envp *)(vars->list_env)->content)->name);
			free(((t_envp *)(vars->list_env)->content)->value);
			free((t_envp *)(vars->list_env)->content);
			*vars->list_env = *tmp_env;
			free(tmp_env);
			continue ;
		}
		while (tmp_env->next)
		{
			if (!ft_strncmp(((t_envp *)tmp_env->next->content)->name, cmd->args[i], 99))
			{
				delet_list(&tmp_env);
				break ;
			}
			tmp_env = tmp_env->next;
		}
	}
	new_envp(vars);
}
