/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:56:13 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/15 16:39:00 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	start_shlvl(t_list **list_env, char **env)
{
	t_list *tmp_list;
	char	*lvl;
	int		i;

	lvl = ft_itoa(ft_atoi(get_env_value(list_env, "SHLVL")) + 1);
	tmp_list = *list_env;
	i = 0;
	while (tmp_list)
	{
		if (!ft_strncmp(((t_envp *)tmp_list->content)->name, "SHLVL", 6))
		{
			((t_envp *)tmp_list->content)->value = lvl;
			env[i] = ft_strjoin_free("SHLVL", "=", 0);
			env[i] = ft_strjoin_free(env[i], lvl, 1);
		}
		tmp_list = tmp_list->next;
		i++;
	}
}
