/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 04:44:20 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/12 17:41:55 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	make_echo(t_command *cmd)
{
	int		i;
	int		args_count;
	int		flag;

	flag = 0;
	args_count = ft_array_len(cmd->args);
	if (args_count == 1)
	{
		write(cmd->fd[1], "\n", 1);
		return ;
	}
	i = 0;
	if (!ft_strncmp(cmd->args[1], "-n", ft_strlen(cmd->args[1])))
	{
		flag = TRUE;
		i++;
	}
	while (cmd->args[++i])
	{
		write(cmd->fd[1], cmd->args[i], ft_strlen(cmd->args[i]));
		if (i != args_count - 1)
			write(cmd->fd[1], " ", 1);
		else if (i == args_count - 1 && !flag)
			write(cmd->fd[1], "\n", 1);
	}
}
