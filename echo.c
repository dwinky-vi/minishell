/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 04:44:20 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/23 03:05:26 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

int	check_flag(t_command *cmd, int *flag)
{
	int		i;
	int		j;
	int		count;

	count = 0;
	i = 0;
	while (cmd->args[++i])
	{
		if (!ft_strncmp(cmd->args[i], "-", 1))
		{
			j = 0;
			while (cmd->args[i][++j])
				if (cmd->args[i][j] != 'n')
					break ;
			if (cmd->args[i][j] == '\0')
			{
				*flag = TRUE;
				count++;
			}
			else
				break ;
		}
	}
	return (count);
}

void	make_echo(t_command *cmd, t_vars *vars)
{
	int		i;
	int		args_count;
	int		flag;

	flag = FALSE;
	args_count = ft_array_len(cmd->args);
	if (args_count == 1 || cmd->args[1][0] == '\0')
	{
		write(cmd->fd[1], "\n", 1);
		return ;
	}
	i = check_flag(cmd, &flag);
	while (cmd->args[++i])
	{
		if (!ft_strncmp(cmd->args[i], "$_", 3))
			cmd->args[i] = vars->command;
		write(cmd->fd[1], cmd->args[i], ft_strlen(cmd->args[i]));
		if (i != args_count - 1)
			write(cmd->fd[1], " ", 1);
		else if (i == args_count - 1 && !flag)
			write(cmd->fd[1], "\n", 1);
	}
}
