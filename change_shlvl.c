/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:56:13 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/16 03:23:21 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	start_shlvl(t_vars *vars)
{
	t_list *tmp_list;
	char	*lvl;
	char	*tmp_lvl;
	int		i;

	tmp_lvl = get_env_value(vars->list_env, "SHLVL");
	lvl = ft_itoa(ft_atoi(tmp_lvl) + 1);
	free(tmp_lvl);
	tmp_list = vars->list_env;
	i = 0;
	while (tmp_list)
	{
		if (!ft_strncmp(((t_envp *)tmp_list->content)->name, "SHLVL", 6))
		{
			((t_envp *)tmp_list->content)->value = lvl;
			vars->envp[i] = ft_strjoin_free("SHLVL", "=", 0);
			vars->envp[i] = ft_strjoin_free(vars->envp[i], lvl, 1);
		}
		tmp_list = tmp_list->next;
		i++;
	}
}
