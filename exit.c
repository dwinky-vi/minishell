/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 21:34:58 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/15 16:59:59 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	making_exit(t_command *cmd, unsigned char res)
{
	if (cmd->miniflag != 1)
		return_term(&cmd->term);
	exit (res);
}

void	numeric_err(t_command *cmd)
{
	char	*str;

	str = ft_strdup("numeric argument required");
	printf("bash1: %s: %s: %s\n", cmd->args[0], cmd->args[1], str);
	making_exit(cmd, 255);
}

int	check_minus(t_command *cmd)
{
	if (cmd->args[1][0] == '-')
	{
		if (!ft_isdigit_str(cmd->args[1] + 1))
			numeric_err(cmd);
		else if (ft_array_len(cmd->args) > 2)
		{
			ft_putendl_fd("bash2: exit: too many arguments", 1);    //   $? = 1
			return (0);
		}
		making_exit(cmd, ft_atoi((cmd->args[1])));
	}
	return (1);
}

void	make_exit(t_command *cmd, t_list **list_env)
{
	ft_putendl_fd("exit", 1);
	if (!cmd->args[1])
		making_exit(cmd, 0);
	else
	{
		if (!check_minus(cmd))
			return ;
		if (!ft_isdigit_str(cmd->args[1]))
			numeric_err(cmd);
		else if (ft_array_len(cmd->args) > 2)
		{
			ft_putendl_fd("bash3: exit: too many arguments", 1);    //   $? = 1
			return ;
		}
		making_exit(cmd, ft_atoi((cmd->args[1])));
	}
}
