/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 06:19:46 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/20 17:00:25 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	dot_err(void)
{
	ft_putendl_fd("minishell: .: filename argument required", 1);
	ft_putendl_fd(".: usage: . filename [arguments]", 1);
	exit(2);
}

void	check_absolute_path(t_command *cmd, char **env)
{
	struct stat	buf;

	if (ft_array_len(cmd->args) == 1 && !ft_strncmp(cmd->args[0], ".", 2))
		dot_err();
	if (!lstat(cmd->args[0], &buf))
	{
		if (S_ISDIR(buf.st_mode))
		{
			printf("minishell: %s: %s\n", cmd->args[0], strerror(EISDIR));
			exit (126);
		}
		if (execve(cmd->args[0], cmd->args, env) == -1 && errno != ENOEXEC)
		{
			printf("minishell: %s: %s\n", cmd->args[0], strerror(errno));
			exit(126);
		}
	}
	else
	{
		printf("minishell: %s: %s\n", cmd->args[0], strerror(errno));
		exit(127);
	}
	exit(0);
}

char	*find_path(t_command *cmd, char *paths)
{
	char		**path_arr;
	char		*path;
	struct stat	buf;
	int			i;

	path_arr = ft_split(paths, ':');
	if (!path_arr)
		return (NULL);
	i = -1;
	while (path_arr[++i])
	{
		path_arr[i] = ft_strjoin_free(path_arr[i], "/", 1);
		if (!path_arr[i])
			mem_err();
		path = ft_strjoin_free(path_arr[i], cmd->args[0], 1);
		if (!path)
			mem_err();
		if (!lstat(path, &buf))
			return (path);
	}
	return (NULL);
}

void	make_other(t_command *cmd, t_list *list_env, char **envp)
{
	char		*paths;
	char		*path;

	if (cmd->args[0][0] == '/' || cmd->args[0][0] == '.')
		check_absolute_path(cmd, envp);
	else
	{
		paths = get_env_value(list_env, "PATH");
		path = find_path(cmd, paths);
		if (!path)
		{
			if (!paths)
				printf("minishell: %s: %s\n", cmd->args[0], strerror(ENOENT));
			else
				printf("minishell: %s: %s\n", cmd->args[0], "command not found");
		}
		else if (execve(path, cmd->args, envp) == -1)
		{
			printf("minishell: %s: %s\n", path, strerror(errno));
			exit(126);
		}
	}
	exit(127);
}
