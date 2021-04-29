/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:58:51 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/29 19:57:01 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

int	parser(char *line, t_vars *vars)
{
	t_command	command;
	size_t		k;

	if (preparing_parser(&line, &k, &command) == FAILURE_CODE)
		return (FAILURE_CODE);
	while (line[k])
	{
		preparing_new_command(line, &k, &command);
		while (line[k])
		{
			if (parsing_0(line, &k, vars, &command) == FAILURE_CODE)
				return (FAILURE_CODE);
			else
				break ;
		}
		preprocessing(&command, vars);
		go_to_parse_next_command(vars, line, &k);
	}
	free(command.args);
	free(line);
	return (SUCCESS_CODE);
}
