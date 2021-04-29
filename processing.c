/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 03:26:37 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/29 04:11:06 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	what_command(t_command *cmd, t_vars *vars)
{
	int			name_len;

	if (ft_array_len(cmd->args) == 1 && cmd->args[0][0] == '\0')
	{
		shell_err(cmd->args, cmd->fd[1], 127, "command not found");
		return ;
	}
	name_len = ft_strlen(cmd->args[0]) + 1;
	if (!ft_strncmp(cmd->args[0], "echo", name_len))
		make_echo(cmd);
	else if (!ft_strncmp(cmd->args[0], "pwd", name_len))
		make_pwd();
	else if (!ft_strncmp(cmd->args[0], "cd", name_len))
		make_cd(cmd, vars);
	else if (!ft_strncmp(cmd->args[0], "env", name_len) && \
				get_env_value(vars->list_env, "PATH"))
		make_env(vars->list_env);
	else if (!ft_strncmp(cmd->args[0], "unset", name_len))
		make_unset(cmd, vars);
	else if (!ft_strncmp(cmd->args[0], "export", name_len))
		make_export(cmd, vars);
	else if (!ft_strncmp(cmd->args[0], "exit", name_len))
		make_exit(cmd, vars);
	else
		make_other(cmd, vars);
}

void	processing(t_command *cmd, t_vars *vars)
{
	if (!vars->f_redir_0)
		cmd->fd[0] = 0;
	if (!vars->f_redir_1)
		cmd->fd[1] = 1;
	if (cmd->args[0])
		what_command(cmd, vars);
	dup2(vars->tmp_fd_0, 0);
	dup2(vars->tmp_fd_1, 1);
}

void	preprocessing(t_command *cmd, t_vars *vars)
{
	int		args_count;
	char	**tmp;

	g_code = 0;
	args_count = ft_array_len(cmd->args) - 1;
	tmp = change_env(vars->list_env, "_");
	free(*tmp);
	if (cmd->args[0] && cmd->args[args_count][0] != '-')
	{
		*tmp = ft_strdup(cmd->args[args_count]);
		new_envp(vars);
	}
	else
		*tmp = ft_strdup("");
	if (vars->f_pipe == TRUE)
		make_pipe(cmd, vars);
	else
		processing(cmd, vars);
	if (vars->f_redir_0)
		close(cmd->fd[0]);
	if (vars->f_redir_1)
		close(cmd->fd[1]);
	free_command(cmd);
}
