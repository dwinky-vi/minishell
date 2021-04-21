/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:56:13 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/18 21:52:55 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	check_lvl(char **tmp_lvl, char **lvl)
{
	if (ft_atoi(*lvl) >= 1000)
	{
		if (ft_atoi(*lvl) == 1000)
			*tmp_lvl = ft_strdup("");
		else
		{
			ft_putstr_fd("minishell: warning: shell level (", 1);
			ft_putstr_fd(*lvl, 1);
			ft_putendl_fd(") too high, resetting to 1", 1);
			*tmp_lvl = ft_strdup("1");
		}
		free(*lvl);
		*lvl = *tmp_lvl;
	}
}

void	init_shlvl(t_vars *vars, char **tmp_lvl, char **lvl)
{
	*tmp_lvl = get_env_value(vars->list_env, "SHLVL");
	*lvl = ft_itoa(ft_atoi(*tmp_lvl) + 1);
	free(*tmp_lvl);
	check_lvl(tmp_lvl, lvl);
}

void	check_shlvl(t_vars *vars)
{
	t_list	*tmp_list;
	char	*tmp_lvl;
	char	*lvl;
	int		i;

	tmp_list = vars->list_env;
	i = 0;
	while (tmp_list)
	{
		if (!ft_strncmp(((t_envp *)tmp_list->content)->name, "SHLVL", 6))
		{
			init_shlvl(vars, &tmp_lvl, &lvl);
			((t_envp *)tmp_list->content)->value = lvl;
			free(vars->envp[i]);
			vars->envp[i] = ft_strjoin_free("SHLVL=", lvl, 0);
			break ;
		}
		tmp_list = tmp_list->next;
		i++;
	}
	if (!tmp_list)
	{
		add_list_env("SHLVL=1", vars->list_env);
		add_envp(vars, "SHLVL=1");
	}
}

void	check_pwd(t_vars *vars)
{
	char	buf[BUFSIZE];
	t_list	*tmp_list;
	char	*tmp_pwd;

	getcwd(buf, BUFSIZE);
	tmp_list = vars->list_env;
	while (tmp_list)
	{
		if (!ft_strncmp(((t_envp *)tmp_list->content)->name, "PWD", 4))
		{
			free(((t_envp *)tmp_list->content)->value);
			((t_envp *)tmp_list->content)->value = ft_strdup(buf);
			break ;
		}
		tmp_list = tmp_list->next;
	}
	if (!tmp_list)
	{
		tmp_pwd = ft_strjoin("PWD=", buf);
		add_list_env(tmp_pwd, vars->list_env);
		add_envp(vars, tmp_pwd);
		free(tmp_pwd);
	}
}

void	init_env(t_vars *vars)
{
	t_list	*tmp_list;

	check_shlvl(vars);
	check_pwd(vars);
	tmp_list = vars->list_env;
	while (tmp_list->next)
	{
		if (!ft_strncmp(((t_envp *)tmp_list->next->content)->name, "OLDPWD", 7))
		{
			delet_list(&tmp_list);
			new_envp(vars);
			break ;
		}
		tmp_list = tmp_list->next;
	}
}
