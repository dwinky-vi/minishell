/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 06:19:46 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/28 12:58:56 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

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

void	check_absolute_path(t_command *cmd, char **env, int	fd_1)
{
	struct stat	buf;

	if (ft_array_len(cmd->args) == 1 && !ft_strncmp(cmd->args[0], ".", 2))
		dot_err(fd_1);
	if (!lstat(cmd->args[0], &buf))
	{
		if (S_ISDIR(buf.st_mode))
		{
			shell_err(cmd->args, fd_1, 126, strerror(EISDIR));
			exit (126);
		}
		if (execve(cmd->args[0], cmd->args, env) == -1 && errno != ENOEXEC)
		{
			shell_err(cmd->args, fd_1, 126, strerror(errno));
			exit(126);
		}
	}
	else
	{
		shell_err(cmd->args, fd_1, 127, strerror(errno));
		exit(127);
	}
	exit(0);
}

void	child_process(t_command *cmd, t_list *list_env, char **envp, int fd_1)
{
	char		*paths;
	char		*path;

	if (cmd->args[0][0] == '/' || cmd->args[0][0] == '.')
		check_absolute_path(cmd, envp, fd_1);
	else
	{
		paths = get_env_value(list_env, "PATH");
		path = find_path(cmd, paths);
		if (!path)
		{
			if (!paths)
				shell_err(cmd->args, fd_1, 127, strerror(ENOENT));
			else
				shell_err(cmd->args, fd_1, 127, "command not found");
		}
		else if (execve(path, cmd->args, envp) == -1)
		{
			shell_err(cmd->args, fd_1, 126, strerror(errno));
			exit(126);
		}
	}
	exit(127);
}

void	parent_process(t_command *cmd, t_vars *vars)
{
	int			status;

	if (!vars->miniflag)
	{
		signal(SIGINT, &parent_signal);
		signal(SIGQUIT, &parent_signal);
	}
	else if (vars->miniflag)
	{
		signal(SIGINT, &child_signal);
		signal(SIGQUIT, &child_signal);
	}
	return_term(&vars->term);
	wait(&status);
	init_term(&vars->term, get_term_name(vars->list_env));
	if (ft_strnstr(cmd->args[0], "minishell", BUFSIZE))
		g_code = status / 256;
	else if (g_code != 130 && g_code !=131)
		g_code = status / 256;
}

void	make_other(t_command *cmd, t_vars *vars)
{
	pid_t		pid;

	if (ft_strnstr(cmd->args[0], "minishell", BUFSIZE))
		cmd->args[1] = ft_strdup("child");
	pid = fork();
	if (pid < 0)
		return ;
	else if (pid == 0)
		child_process(cmd, vars->list_env, vars->envp, vars->tmp_fd_1);
	else
		parent_process(cmd, vars);
}
