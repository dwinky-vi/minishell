/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocessing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 03:17:19 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/25 06:12:35 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void    preprocessing(t_command *cmd, t_vars *vars)
{
    signal_on();
    if (vars->f_pipe == TRUE) //			!!!
        make_pipe_or_redir(cmd, vars); //						!!!
    else //															!!!
        processing(cmd, vars); //								!!!
	if (vars->f_redir)
	{
		close(cmd->fd[1]);
		close(cmd->fd[0]);
	}
    vars->f_pipe = FALSE;
    vars->f_redir = FALSE;
    signal_off();
}
