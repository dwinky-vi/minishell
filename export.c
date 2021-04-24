/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 21:17:25 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/25 02:29:30 by aquinoa          ###   ########.fr       */
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

char	**sort_env(t_list *list_env)
{
	char	**env;
	int		i;
	int		j;
	char	*tmp_env;
	t_list	*tmp_list;

	tmp_list = list_env;
	env = (char **)ft_calloc(ft_lstsize(tmp_list) + 1, sizeof(char *));
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
	while (++i < ft_array_len(env) - 1)
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

void	making_export(t_list *list_env, int fd_1)
{
	char	**env;
	int		i;

	env = sort_env(list_env);
	i = -1;
	while (env[++i])
	{
		ft_putendl_fd(env[i], fd_1);
	}
	ft_free_array(env);
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

void	adding_variable()
{

}

void	add_variable(t_command *cmd, t_vars *vars)
{
	char	*key;
	char	*value;
	int		equal;
	int		i;
	char	**env_value;

	i = 0;
	while (cmd->args[++i])
	{
		if (cmd->args[i][0] == '=')
		{
			env_err(cmd, i);
			continue ;
		}
		equal = equal_sign(cmd->args[i]); //	+=	!!!!
		if (!equal)
		{
			env_err(cmd, i);
			continue ;
		}

		key = ft_substr(cmd->args[i], 0, equal);
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
		making_export(vars->list_env, cmd->fd[1]);
	else
	{
		add_variable(cmd, vars);
	}
	new_envp(vars);
}
