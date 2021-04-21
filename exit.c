/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 21:34:58 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/20 03:00:47 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	making_exit(t_vars *vars, unsigned char res)
{
	if (vars->miniflag != 1)
		return_term(&vars->term);
	exit (res);
}

void	numeric_err(t_command *cmd, t_vars *vars)
{
	char	*str;

	str = ft_strdup("numeric argument required");
	printf("minishell: %s: %s: %s\n", cmd->args[0], cmd->args[1], str);
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
			ft_putendl_fd("minishell: exit: too many arguments", 1);
			g_code = 1;
			return (0);
		}
		making_exit(vars, ft_atoi((cmd->args[1])));
	}
	return (1);
}

void	make_exit(t_command *cmd, t_vars *vars)
{
	ft_putendl_fd("exit", 1);
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
			ft_putendl_fd("minishell: exit: too many arguments", 1);
			g_code = 1;
			return ;
		}
		making_exit(vars, ft_atoi((cmd->args[1])));
	}
}
