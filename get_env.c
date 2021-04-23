/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 17:28:09 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/22 20:59:29 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

static t_envp	*parse_env(char *str)
{
	t_envp	*env;
	size_t	k;

	k = 0;
	env = (t_envp *)ft_calloc(1, sizeof(t_envp));
	if (env == NULL)
		mem_err();
	while (str[k] != '=')
		k++;
	str[k] = '\0';
	env->name = ft_strdup(str);
	if (env->name == NULL)
		mem_err();
	str[k] = '=';
	k++;
	env->value = ft_strdup(str + k);
	if (env->value == NULL)
		mem_err();
	return (env);
}

void		get_env_to_lst(t_vars *vars)
{
	t_list	*head;
	t_envp	*cur_envp;
	t_list	*lst;
	char	**envp_copy;

	envp_copy = vars->envp;
	head = NULL;
	while (*envp_copy)
	{
		cur_envp = parse_env(*envp_copy);
		if (cur_envp == NULL)
			mem_err();
		lst = ft_lstnew(cur_envp);
		if (lst == NULL)
			mem_err();
		ft_lstadd_back(&head, lst);
		envp_copy++;
	}
	vars->list_env = head;
}
