/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 19:15:40 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/15 20:33:32 by aquinoa          ###   ########.fr       */
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

void	make_unset(t_command *cmd, t_list **list_env)
{
	t_list	*tmp_env;
	int		i;

	i = 0;
	while (cmd->args[++i])
	{
		tmp_env = *list_env;
		if (!ft_strncmp(((t_envp *)tmp_env->content)->name, cmd->args[i], BUFSIZE))
		{
			tmp_env = (*list_env)->next;
			free(((t_envp *)(*list_env)->content)->name);
			free(((t_envp *)(*list_env)->content)->value);
			free((t_envp *)(*list_env)->content);
			**list_env = *tmp_env;
			continue ;
		}
		while (tmp_env->next)
		{
			if (!ft_strncmp(((t_envp *)tmp_env->next->content)->name, cmd->args[i], BUFSIZE))
			{
				delet_list(&tmp_env);
				break ;
			}
			tmp_env = tmp_env->next;
		}
	}
}
