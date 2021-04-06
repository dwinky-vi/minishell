/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 06:19:46 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/06 18:29:43 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	making_other(t_command *cmd, char **path_arr, char **av_tmp, char *path)
{
	int			i;
	struct stat	buf;

	i = -1;
	while (cmd->args[++i])
		av_tmp[i + 1] = cmd->args[i];
	if (!lstat(cmd->name, &buf))
		execve(cmd->name, av_tmp, cmd->env);
	i = -1;
	while (path_arr[++i])
	{
		path_arr[i] = ft_strjoin(path_arr[i], "/", 1);
		if (!path_arr[i])
			exit(0);
		path = ft_strjoin(path_arr[i], cmd->name, 1);
		if (!path)
			exit(0);
		if (!lstat(path, &buf))
			execve(path, av_tmp, cmd->env);
		free(path);
	}
}

void	make_other(t_command *cmd, t_list *envp, char **env)
{
	char		**path_arr;
	char		**av_tmp;
	char		*paths;
	int			i;

	av_tmp = ft_calloc(ft_array_len(cmd->args) + 2, sizeof(char *));
	if (!av_tmp)
		exit(0);
	paths = ft_substr(cmd->env[16], 5, BUFSIZE);
	ft_putendl_fd(cmd->env[16], 1);
	// free(paths);
	path_arr = ft_split(paths, ':');
	if (!path_arr)
		exit(0);
	av_tmp[0] = cmd->name;
	making_other(cmd, path_arr, av_tmp, paths);
	if (cmd->name[0] != '/' && cmd->env[16][5] == '/')
		printf("bash: %s: %s\n", cmd->name, "command not found");
	else
		printf("bash: %s: %s\n", cmd->name, strerror(errno));
	exit(0);
}
