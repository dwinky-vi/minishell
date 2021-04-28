/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 18:55:00 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/27 19:22:15 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	sorting_env(t_list *list, char ***env)
{
	int		i;
	int		j;
	char	*tmp_env;

	i = -1;
	while (++i < ft_lstsize(list) - 1)
	{
		j = i + 1;
		if (ft_strncmp((*env)[i], (*env)[j], BUFSIZE) > 0)
		{
			tmp_env = (*env)[i];
			(*env)[i] = (*env)[j];
			(*env)[j] = tmp_env;
			i = -1;
		}
	}
}

char	*make_env_arr(t_list *list, int flag)
{
	char	*env;

	if (flag)
	{
		env = ft_strjoin("declare -x ", ((t_envp *)list->content)->name);
		if (!env)
			mem_err();
		env = ft_strjoin_free(env, "=\"", 1);
		if (!env)
			mem_err();
		env = ft_strjoin_free(env, ((t_envp *)list->content)->value, 1);
		if (!env)
			mem_err();
		env = ft_strjoin_free(env, "\"", 1);
		if (!env)
			mem_err();
	}
	else
	{
		env = ft_strjoin("declare -x ", list->content);
		if (!env)
			mem_err();
	}
	return (env);
}

char	**sort_env(t_list *list, int flag)
{
	char	**env;
	int		i;
	t_list	*tmp_list;

	tmp_list = list;
	env = (char **)ft_calloc(ft_lstsize(tmp_list) + 1, sizeof(char *));
	if (!env)
		mem_err();
	i = 0;
	while (tmp_list)
	{
		env[i] = make_env_arr(tmp_list, flag);
		tmp_list = tmp_list->next;
		i++;
	}
	sorting_env(list, &env);
	return (env);
}

void	del_exp(t_list *exp)
{
	t_list	*previous;
	t_list	*del_list;
	t_list	*following;

	previous = exp;
	del_list = exp->next;
	following = del_list->next;
	free(del_list->content);
	free(del_list);
	previous->next = following;
}

void	check_exp(t_vars *vars, char *str)
{
	t_list	*tmp;

	tmp = vars->export;
	if (!ft_strncmp(tmp->content, str, BUFSIZE))
	{
		vars->export = vars->export->next;
		free(tmp->content);
		free(tmp);
		return ;
	}
	tmp = vars->export;
	while (tmp->next)
	{
		if (!ft_strncmp(tmp->next->content, str, BUFSIZE))
		{
			del_exp(tmp);
			break ;
		}
		tmp = tmp->next;
	}
}
