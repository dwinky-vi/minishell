/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:42:48 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/30 01:18:45 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_vars		vars;
	t_history	history;

	preparing(argc, argv, envp, &vars);
	get_history(&history, &vars);
	ft_termcap(&history, &vars);
	return (return_func(&vars, &history));
}
