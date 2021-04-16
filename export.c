/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 21:17:25 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/16 03:21:59 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	add_env(char *str, t_list *list_env)
{
	t_envp	*new_env;
	int		i;

	new_env = (t_envp *)malloc(sizeof(t_envp));
	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			break ;
	}
	new_env->name = ft_substr(str, 0, i);
	new_env->value = ft_substr(str, ++i, BUFSIZE);
	ft_lstadd_back(&list_env, ft_lstnew(new_env));
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
	return 0;
}

char	*make_env_arr(t_list *list_env)
{
	char	*env;

	env = ft_strjoin("declare -x ", ((t_envp *)list_env->content)->name);
	env = ft_strjoin_free(env, "=\"", 1);
	env = ft_strjoin_free(env, ((t_envp *)list_env->content)->value, 1);
	env = ft_strjoin_free(env, "\"", 1);
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

void	making_export(t_list *list_env)
{
	char	**env;
	int		i;

	env = sort_env(list_env);
	i = -1;
	while (env[++i])
	{
		ft_putendl_fd(env[i], 1);
	}
	ft_free_array(env);
}

// void	check_args(t_command *cmd, t_list **list_env)
// {
// 	int		i;
// 	int		j;

// 	i = -1;
// 	while (cmd->args[++i])
// 	{
// 		j = -1;
// 		while (cmd->args[i][++j])
// 		{
// 			if (cmd->args[i][j] == '=')
// 			{
// 				if (cmd->args[i][j - 1] == ' ' || cmd->args[i][j + 1] == ' ')
// 					printf("bash: %s: %s: not a valid identifier\n", cmd->args[0], cmd->args[1]);
// 			}
// 		}
// 	}
// }

void	make_export(t_command *cmd, t_list *list_env)
{
	t_list	*tmp_env;
	char	*key;
	char	*value;
	int		equal;
	int		i;

	char	**env_value;

	if (!cmd->args[1])
		making_export(list_env);
	else
	{
		i = 0;
		while (cmd->args[++i])
		{
			equal = equal_sign(cmd->args[i]);
			if (!equal)								//!!!!
				return ;
			key = ft_substr(cmd->args[i], 0, equal);
			value = ft_substr(cmd->args[i], ++equal, BUFSIZE);
			if (!get_env_value(list_env, key))
				add_env(cmd->args[i], list_env);
			else
			{
				env_value = change_env(list_env, key);
				free(*env_value);
				*env_value = ft_strdup(value);
			}
			free(key);
			free(value);
		}
	}
}
