/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 06:19:46 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/12 17:53:06 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

int	check_absolute_path(t_command *cmd, char **env)
{
	struct stat	buf;

	if (!lstat(cmd->args[0], &buf))
	{
		if (execve(cmd->args[0], cmd->args, env) == -1)
			return (0);
	}
	else
		return (0);
	return (1);
}

// char	**init_new_argv(t_command *cmd)
// {
// 	char	**argv;
// 	int		i;

// 	argv = ft_calloc(ft_array_len(cmd->args) + 2, sizeof(char *));
// 	if (!argv)
// 		mem_err();
// 	argv[0] = cmd->args[0];
// 	i = -1;
// 	while (cmd->args[++i])
// 		argv[i + 1] = cmd->args[i];
// 	return (argv);
// }

char	*find_path(t_command *cmd, t_list **list_env, char *paths)
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

void	making_other(t_command *cmd, char *path, char **env)
{
	if (execve(path, cmd->args, env) == -1)
		printf("bash: %s: %s\n", cmd->args[0], strerror(errno));
}

void	make_other(t_command *cmd, t_list **list_env, char **envp)
{
	// char		**argv;
	char		*paths;
	char		*path;

	// argv = init_new_argv(cmd);
	if (cmd->args[0][0] == '/' || cmd->args[0][0] == '.')
	{
		if (!ft_strncmp(cmd->args[0], "/", 2))
			printf("bash: %s: %s\n", cmd->args[0], strerror(EISDIR));
		else
			if (!check_absolute_path(cmd, envp) && errno != ENOEXEC)
				printf("bash: %s: %s\n", cmd->args[0], strerror(errno));
	}
	else
	{
		paths = get_env_value(list_env, "PATH");
		path = find_path(cmd, list_env, paths);
		if (!path)
		{
			if (!paths)
				printf("bash: %s: %s\n", cmd->args[0], strerror(ENOENT));
			else
				printf("bash: %s: %s\n", cmd->args[0], "command not found");
		}
		else
			making_other(cmd, path, envp);
	}
	exit(0);
}
