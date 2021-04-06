/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 05:20:25 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/05 16:19:11 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	make_cd(t_command *cmd)
{
	if (chdir(cmd->args[0]) == -1)
		printf("bash: %s: %s: %s\n", cmd->name, cmd->args[0], strerror(errno));
}
