/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:58:51 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/29 21:55:18 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"
#include "stdio.h"

int	parser(char *line, t_vars *vars)
{
	t_command	command;
	size_t		r;
	size_t		k;

	if (preparing_parser(&line, &k, &command) == FAILURE_CODE)
		return (FAILURE_CODE);
	while (line[k])
	{
		preparing_new_command(line, &k, &command);
		while (line[k])
		{
			r = parsing_0(line, &k, vars, &command);
			if (r == FAILURE_CODE)
				return (FAILURE_CODE);
			else if (r == BREAK_CODE)
				break ;
		}
		preprocessing(&command, vars);
		go_to_parse_next_command(vars, line, &k);
	}
	free(command.args);
	free(line);
	return (SUCCESS_CODE);
}
