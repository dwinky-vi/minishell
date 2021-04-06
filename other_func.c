/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 06:19:46 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/06 20:48:03 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	making_other(t_command *cmd, char **path_arr, char **av_tmp, char **envp)
{
	int			i;
	struct stat	buf;
	char		*path;

	i = -1;
	while (cmd->args[++i])
		av_tmp[i + 1] = cmd->args[i];
	if (!lstat(cmd->name, &buf))
		execve(cmd->name, av_tmp, envp);
	i = -1;
	while (path_arr[++i])
	{
		path_arr[i] = ft_strjoin_free(path_arr[i], "/", 1);
		if (!path_arr[i])
			exit(0);
		path = ft_strjoin_free(path_arr[i], cmd->name, 1);
		if (!path)
			exit(0);
		if (!lstat(path, &buf))
			execve(path, av_tmp, envp);
		free(path);
	}
}

void	make_other(t_command *cmd, t_list *list_env, char **envp)
{
	char		**path_arr;
	char		**av_tmp;
	char		*paths;
	int			i;
	t_list		*head;

	head = list_env;
	av_tmp = ft_calloc(ft_array_len(cmd->args) + 2, sizeof(char *));
	if (!av_tmp)
		exit(0);
	paths = "";
	while (list_env)
	{
		if (!ft_strncmp(((t_envp *)list_env->content)->name, "PATH", ft_strlen(((t_envp *)list_env->content)->name)))
		{
			paths = ft_strdup(((t_envp *)list_env->content)->value);
			break ;
		}
		list_env = list_env->next;
	}
	path_arr = ft_split(paths, ':');
	if (!path_arr)
		exit(0);
	av_tmp[0] = cmd->name;
	making_other(cmd, path_arr, av_tmp, envp);
	if (cmd->name[0] != '/' && paths[0] == '/')
		printf("bash: %s: %s\n", cmd->name, "command not found");
	else
		printf("bash: %s: %s\n", cmd->name, strerror(errno));
	exit(0);
}
