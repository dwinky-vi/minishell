/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 21:17:25 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/26 13:15:23 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	add_list_env(char *str, t_list *list_env)
{
	t_envp	*new_env;
	int		i;
	t_list	*new_list;

	new_env = (t_envp *)malloc(sizeof(t_envp));
	if (!new_env)
		mem_err();
	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			break ;
	}
	new_env->name = ft_substr(str, 0, i);
	if (!new_env->name)
		mem_err();
	new_env->value = ft_substr(str, ++i, BUFSIZE);
	if (!new_env->value)
		mem_err();
	new_list = ft_lstnew(new_env);
	if (!new_list)
		mem_err();
	ft_lstadd_back(&list_env, new_list);
}

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

char	*make_env_arr(t_list *list_env)
{
	char	*env;

	env = ft_strjoin("declare -x ", ((t_envp *)list_env->content)->name);
	if (!env)
		mem_err();
	env = ft_strjoin_free(env, "=\"", 1);
	if (!env)
		mem_err();
	env = ft_strjoin_free(env, ((t_envp *)list_env->content)->value, 1);
	if (!env)
		mem_err();
	env = ft_strjoin_free(env, "\"", 1);
	if (!env)
		mem_err();
	return (env);
}

char	**sort_env(t_vars *vars)
{
	char	**env;
	int		i;
	int		j;
	char	*tmp_env;
	t_list	*tmp_list;

	tmp_list = vars->list_env;
	env = (char **)ft_calloc(ft_lstsize(tmp_list) + ft_lstsize(vars->export) + 1, sizeof(char *));
	if (!env)
		mem_err();
	i = 0;
	while (tmp_list)
	{
		env[i] = make_env_arr(tmp_list);
		tmp_list = tmp_list->next;
		i++;
	}
	i = -1;
	while (++i < ft_lstsize(tmp_list) - 1)
	{
		j = i + 1;
		if (ft_strncmp(env[i], env[j], BUFSIZE) > 0)
		{
			tmp_env = env[i];
			env[i] = env[j];
			env[j] = tmp_env;
			i = -1;
		}
	}
	return (env);
}

void	making_export(t_vars *vars, int fd_1)
{
	char	**env;
	int		i;

	t_list *tmp_list;

	env = sort_env(vars);
	i = -1;
	while (env[++i])
	{
		ft_putendl_fd(env[i], fd_1);
	}
	ft_free_array(env);
	tmp_list = vars->export;
	while (tmp_list)
	{
		ft_putstr_fd("declare -x ", fd_1);
		ft_putendl_fd(tmp_list->content, fd_1);
		tmp_list = tmp_list->next;
	}
}

int	check_key(t_command *cmd, char *key, int i)
{
	int		j;

	j = -1;
	if (!ft_isalpha(key[0]))
	{
		env_err(cmd, i);
		return (0);
	}
	while (key[++j])
	{
		if (!ft_isalnum(key[j]))
		{
			env_err(cmd, i);
			return (0);
		}
	}
	return (1);
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

void	add_variable(t_command *cmd, t_vars *vars)
{
	char	*key;
	char	*value;
	int		equal;
	int		i;
	char	**env_value;
	t_list	*lst;

	i = 0;
	while (cmd->args[++i])
	{
		ft_putendl_fd(cmd->args[i], 1);
		if (cmd->args[i][0] == '=')
		{
			env_err(cmd, i);
			continue ;
		}
		equal = equal_sign(cmd->args[i]); //	+=	!!!!
		if (!equal)
		{
			if (!check_key(cmd, cmd->args[i], i))
				continue ;
			else
			{
				lst = vars->list_env;
				while (lst)
				{
					if (!ft_strncmp(((t_envp *)lst->content)->name, cmd->args[i], BUFSIZE))
						break ;
					lst = lst->next;
				}
				if (lst != NULL)
					continue ;
				lst = vars->export;
				while (lst)
				{
					if (!ft_strncmp(lst->content, cmd->args[i], BUFSIZE))
						break ;
					lst = lst->next;
				}
				if (lst != NULL)
					continue ;
				lst = ft_lstnew(ft_strdup(cmd->args[i]));
				if (!lst)
					mem_err();
				ft_lstadd_back(&vars->export, lst);
			}
			continue ;
		}
		key = ft_substr(cmd->args[i], 0, equal);
		if (vars->export)
			check_exp(vars, key);
		if (!key)
			mem_err();
		if (!check_key(cmd, key, i))
		{
			free(key);
			continue ;
		}
		value = ft_substr(cmd->args[i], ++equal, BUFSIZE);
		if (!get_env_value(vars->list_env, key))
			add_list_env(cmd->args[i], vars->list_env);
		else
		{
			env_value = change_env(vars->list_env, key);
			free(*env_value);
			*env_value = ft_strdup(value);
			if (!env_value)
				mem_err();
		}
		free(key);
		free(value);
	}
}

void	make_export(t_command *cmd, t_vars *vars)
{

	if (!cmd->args[1])
		making_export(vars, cmd->fd[1]);
	else
	{
		add_variable(cmd, vars);
	}
	new_envp(vars);
}
