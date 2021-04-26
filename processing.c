/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 03:26:37 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/26 20:49:41 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	mem_err(void)
{
	ft_putendl_fd("Memory error!", 1);
	exit(1);
}

void	shell_err(char **args, int fd_1, int code, char *str)
{
	dup2(fd_1, 1);

	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(args[0], 1);
	ft_putstr_fd(": ", 1);
	ft_putendl_fd(str, 1);
	// printf("minishell: %s: %s\n", args[0], str);

	g_code = code;
}

void	env_err(t_command *cmd, int i)
{
	char	*str;

	str = ft_strjoin("minishell: ", cmd->args[0]);
	str = ft_strjoin_free(str, ": `", 1);
	str = ft_strjoin_free(str, cmd->args[i], 1);
	str = ft_strjoin_free(str, "': not a valid identifier", 1);
	ft_putendl_fd(str, 1);
	free(str);
	g_code = 1;
}

void	for_signal(int param)
{
	// signal (SIGTERM, SIG_IGN);    			// Игнорирует сигнал прерывания процесса  (ЗАЩИТА ОТ kill minishell)
	if (param == 2)
	{
		ft_putstr_fd("\n", 1);
		g_code = 130;
	}
	else if (param == 3)
	{
		ft_putendl_fd("Quit: 3", 1);
		g_code = 131;
	}
	else
		ft_putstr_fd("error\n", 1);
}

void	child_signal(int param)
{
	// signal (SIGTERM, SIG_IGN);    			// Игнорирует сигнал прерывания процесса  (ЗАЩИТА ОТ kill minishell)
	if (param == 2)
	{
		// ft_putstr_fd("\n", 1);
		g_code = 130;
	}
	else if (param == 3)
	{
		// ft_putendl_fd("Quit: 3", 1);
		g_code = 131;
	}
	else
		ft_putstr_fd("error\n", 1);
}

void	borning_child(t_command *cmd, t_vars *vars)
{
	pid_t		pid;
	int			status;

	pid = fork();
	if (pid < 0)
	{
		ft_putendl_fd(strerror(errno), 1);
		return ;
	}
	else if (pid == 0)
	{
		if (ft_strnstr(cmd->args[0], "minishell", BUFSIZE))
			cmd->args[1] = ft_strdup("child");
		make_other(cmd, vars->list_env, vars->envp, vars->tmp_fd_1);
	}
	else
	{
		if (!vars->miniflag)
		{
			signal(SIGINT, &for_signal); // Это ловит ctrl-C.  Код сигнала –– 2
			signal(SIGQUIT, &for_signal); // Это ловит ctrl-\. Код сигнала –– 3
		}
		else if (vars->miniflag)
		{
			signal(SIGINT, &child_signal); // Это ловит ctrl-C.  Код сигнала –– 2
			signal(SIGQUIT, &child_signal); // Это ловит ctrl-\. Код сигнала –– 3
		}
		return_term(&vars->term);
		wait(&status);
		init_term(&vars->term, get_term_name(vars->list_env));
		if (status == 66)
			g_code = 1;
		else if (g_code != 130 && g_code !=131)
			g_code = status / 256;
	}
}

void	processing(t_command *cmd, t_vars *vars)
{
	int			name_len;

	if (!vars->f_redir)
	{
		cmd->fd[0] = 0;
		cmd->fd[1] = 1;
	}
	if (cmd->args[0]) // Обновляй $_ !!!
	{
		if (ft_array_len(cmd->args) == 1 && cmd->args[0][0] == '\0')
		{
			shell_err(cmd->args, cmd->fd[1], 127, "command not found");
			return ;
		}
		name_len = ft_strlen(cmd->args[0]) + 1;
		if (!ft_strncmp(cmd->args[0], "echo", name_len))
			make_echo(cmd, vars);
		else if (!ft_strncmp(cmd->args[0], "pwd", name_len))
			make_pwd(cmd);
		else if (!ft_strncmp(cmd->args[0], "cd", name_len))
			make_cd(cmd, vars);
		else if (!ft_strncmp(cmd->args[0], "env", name_len) && \
					get_env_value(vars->list_env, "PATH"))
			make_env(cmd, vars->list_env);
		else if (!ft_strncmp(cmd->args[0], "unset", name_len))
			make_unset(cmd, vars);
		else if (!ft_strncmp(cmd->args[0], "export", name_len))
			make_export(cmd, vars);
		else if (!ft_strncmp(cmd->args[0], "exit", name_len))
			make_exit(cmd, vars);
		else
			borning_child(cmd, vars);
	}
	dup2(vars->tmp_fd_0, 0); //				!!! Возвращаю stdin fd !!!
	dup2(vars->tmp_fd_1, 1); //				!!! Возвращаю stdout fd !!!
}
