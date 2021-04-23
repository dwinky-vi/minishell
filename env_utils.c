/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 19:47:19 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/23 19:16:42 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	new_envp(t_vars *vars)
{
	t_list	*tmp_list;
	int		i;

	i = -1;
	while (vars->envp[++i])
		free(vars->envp[i]);
	free(vars->envp);
	vars->envp = ft_calloc(ft_lstsize(vars->list_env) + 1, sizeof(char *));
	if (!vars->envp)
		mem_err();
	tmp_list = vars->list_env;
	i = 0;
	while (tmp_list)
	{
		vars->envp[i] = ft_strjoin(((t_envp *)tmp_list->content)->name, "=");
		if (!vars->envp[i])
			mem_err();
		vars->envp[i] = ft_strjoin_free(vars->envp[i], \
					((t_envp *)tmp_list->content)->value, 1);
		if (!vars->envp[i])
			mem_err();
		tmp_list = tmp_list->next;
		i++;
	}
}

void	add_envp(t_vars *vars, char *str)
{
	char	**new_envp;
	int		i;

	new_envp = (char **)ft_calloc(ft_array_len(vars->envp) + 2, sizeof(char *));
	if (!new_envp)
		mem_err();
	i = -1;
	while (vars->envp[++i])
	{
		new_envp[i] = ft_strdup(vars->envp[i]);
		if (!new_envp[i])
			mem_err();
		free(vars->envp[i]);
	}
	free(vars->envp);
	new_envp[i] = ft_strdup(str);
	if (!new_envp[i])
		mem_err();
	vars->envp = new_envp;
}

void	envp_copy(t_vars *vars, char **envp)
{
	int		i;

	vars->envp = (char **)ft_calloc(ft_array_len(envp) + 1, sizeof(char *));
	if (!vars->envp)
		mem_err();
	i = -1;
	while (envp[++i])
	{
		vars->envp[i] = ft_strdup(envp[i]);
		if (!vars->envp[i])
			mem_err();
	}
}

char	**change_env(t_list *list_env, char *key)
{
	t_list	*tmp_list;

	tmp_list = list_env;
	while (tmp_list)
	{
		if (!ft_strncmp(((t_envp *)tmp_list->content)->name, key, BUFSIZE))
			return (&((t_envp *)tmp_list->content)->value);
		tmp_list = tmp_list->next;
	}
	return (NULL);
}

char	*get_env_value(t_list *list_env, char *key)
{
	t_list	*tmp_list;

	tmp_list = list_env;
	while (tmp_list)
	{
		if (!ft_strncmp(((t_envp *)tmp_list->content)->name, key, BUFSIZE))
			return (((t_envp *)tmp_list->content)->value);
		tmp_list = tmp_list->next;
	}
	return (NULL);
}
