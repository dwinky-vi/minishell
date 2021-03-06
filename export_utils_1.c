/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 18:43:39 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/29 01:32:48 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

int	equal_sign(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			return (i);
	}
	return (0);
}

int	check_key(t_command *cmd, char *key, int i, int fd_1)
{
	int		j;

	if (ft_isdigit(key[0]))
	{
		env_err(cmd, i, fd_1);
		return (0);
	}
	j = -1;
	while (key[++j])
	{
		if (key[j] != '_')
		{
			if (!ft_isalnum(key[j]))
			{
				env_err(cmd, i, fd_1);
				return (0);
			}
		}
	}
	return (1);
}

void	add_list_env(char *str, t_list *list_env)
{
	t_envp	*new_env;
	int		i;
	t_list	*new_list;

	new_env = (t_envp *)malloc(sizeof(t_envp));
	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			break ;
	}
	new_env->name = ft_substr(str, 0, i);
	new_env->value = ft_substr(str, ++i, BUFSIZE);
	new_list = ft_lstnew(new_env);
	ft_lstadd_back(&list_env, new_list);
}

void	adding_variable(char *str, t_vars *vars, char *key, char *val)
{
	char	**env_value;

	if (!get_env_value(vars->list_env, key))
		add_list_env(str, vars->list_env);
	else
	{
		env_value = change_env(vars->list_env, key);
		free(*env_value);
		*env_value = ft_strdup(val);
	}
}

int	searching_variable(t_command *cmd, t_vars *vars, int i)
{
	t_list	*lst;

	lst = vars->list_env;
	while (lst)
	{
		if (!ft_strncmp(((t_envp *)lst->content)->name, cmd->args[i], BUFSIZE))
			break ;
		lst = lst->next;
	}
	if (lst != NULL)
		return (1);
	lst = vars->export;
	while (lst)
	{
		if (!ft_strncmp(lst->content, cmd->args[i], BUFSIZE))
			break ;
		lst = lst->next;
	}
	if (lst != NULL)
		return (1);
	return (0);
}
