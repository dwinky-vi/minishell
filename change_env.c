/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 23:39:29 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/13 23:43:41 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

char	**change_env(t_list **list_env, char *key)
{
	t_list	*tmp_list;

	tmp_list = *list_env;
	while(tmp_list)
	{
		if (!ft_strncmp(((t_envp *)tmp_list->content)->name, key, BUFSIZE))
			return (&((t_envp *)tmp_list->content)->value);
		tmp_list = tmp_list->next;
	}
	return (NULL);
}
