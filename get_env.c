/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 17:28:09 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/10 19:39:59 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

static t_envp	*parse_env(char *str)
{
	t_envp	*env;
	size_t	k;

	k = 0;
	env = (t_envp *)ft_calloc(1, sizeof(t_envp));
	while (str[k] != '=')
		k++;
	str[k] = '\0';
	env->name = ft_strdup(str);
	str[k] = '=';
	k++;
	env->value = ft_strdup(str + k);
	return (env);
}

t_list	*get_env(char **envp)
{
	t_list	*lst;
	t_envp	*cur_envp;

	lst = NULL;
	while (*envp)
	{
		cur_envp = parse_env(*envp);
		ft_lstadd_back(&lst, ft_lstnew(cur_envp));
		envp++;
	}
	return (lst);
}
