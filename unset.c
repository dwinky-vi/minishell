/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 19:15:40 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/12 17:45:59 by aquinoa          ###   ########.fr       */
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

	tmp_env = *list_env;
	while (tmp_env->next)
	{
		if (!ft_strncmp(((t_envp *)tmp_env->next->content)->name, cmd->args[1], ft_strlen(cmd->args[0]) + 1))
		{
			delet_list(&tmp_env);
			break ;
		}
		tmp_env = tmp_env->next;
	}
}
