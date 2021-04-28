/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 21:34:58 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/28 17:06:39 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	making_exit(t_vars *vars, unsigned char res)
{
	if (vars->miniflag != 1 && !vars->f_pipe)
		return_term(&vars->term);
	exit (res);
}

void	numeric_err(t_command *cmd, t_vars *vars)
{
	char	*str;

	str = ft_strdup(": numeric argument required");
	if (!str)
		mem_err();
	str = ft_strjoin(cmd->args[1], str);
	if (!str)
		mem_err();
	shell_err(cmd->args, vars->tmp_fd_1, 0, str);
	making_exit(vars, 255);
}

int	check_minus(t_command *cmd, t_vars *vars)
{
	if (cmd->args[1][0] == '-')
	{
		if (!ft_isdigit_str(cmd->args[1] + 1) || \
				!ft_strncmp(cmd->args[1], "-", 2))
			numeric_err(cmd, vars);
		else if (ft_array_len(cmd->args) > 2)
		{
			shell_err(cmd->args, vars->tmp_fd_1, 1, "too many arguments");
			return (0);
		}
		making_exit(vars, ft_atoi((cmd->args[1])));
	}
	return (1);
}

void	make_exit(t_command *cmd, t_vars *vars)
{
	if (!vars->f_pipe)
		ft_putendl_fd("exit", vars->tmp_fd_1);
	if (!cmd->args[1])
		making_exit(vars, 0);
	else
	{
		if (!check_minus(cmd, vars))
			return ;
		if (!ft_isdigit_str(cmd->args[1]))
			numeric_err(cmd, vars);
		else if (ft_array_len(cmd->args) > 2)
		{
			shell_err(cmd->args, vars->tmp_fd_1, 1, "too many arguments");
			return ;
		}
		making_exit(vars, ft_atoi((cmd->args[1])));
	}
}
