/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 02:05:11 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/29 03:19:23 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

static int	set_vars(t_vars *vars, char **envp)
{
	envp_copy(vars, envp);
	get_env_to_lst(vars);
	init_env(vars);
	vars->export = NULL;
	vars->tmp_fd_0 = dup(0);
	vars->tmp_fd_1 = dup(1);
	vars->f_pipe = FALSE;
	vars->f_redir_0 = FALSE;
	vars->f_redir_1 = FALSE;
	return (0);
}

void	preparing(int argc, char **argv, char **envp, t_vars *vars)
{
	if (argc == 2 && ft_strnstr(argv[1], "child", BUFSIZE))
		vars->miniflag = 1;
	set_vars(vars, envp);
	init_term(&vars->term, get_term_name(vars->list_env));
	g_code = 0;
}

int	return_func(t_vars *vars, t_history *history)
{
	if (vars->miniflag != 1)
		return_term(&vars->term);
	set_history(history, vars);
	return (FAILURE_CODE);
}
