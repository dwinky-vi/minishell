/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:51:39 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/29 03:57:08 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

int	syntax_error(char *token)
{
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd("syntax error near unexpected token `", 1);
	ft_putstr_fd(token, 1);
	ft_putstr_fd("'\n", 1);
	g_code = 258;
	return (FAILURE_CODE);
}

void	dot_err(int fd_1)
{
	dup2(fd_1, 1);
	ft_putendl_fd("minishell: .: filename argument required", 1);
	ft_putendl_fd(".: usage: . filename [arguments]", 1);
	exit(2);
}

void	shell_err(char **args, int fd_1, int code, char *str)
{
	dup2(fd_1, 1);
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(args[0], 1);
	ft_putstr_fd(": ", 1);
	ft_putendl_fd(str, 1);
	g_code = code;
}

void	env_err(t_command *cmd, int i, int fd_1)
{
	char	*str;

	dup2(fd_1, 1);
	str = ft_strjoin("minishell: ", cmd->args[0]);
	str = ft_strjoin_free(str, ": `", 1);
	str = ft_strjoin_free(str, cmd->args[i], 1);
	str = ft_strjoin_free(str, "': not a valid identifier", 1);
	ft_putendl_fd(str, 1);
	free(str);
	g_code = 1;
}
