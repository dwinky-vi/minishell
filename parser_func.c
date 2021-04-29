/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 17:18:45 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/29 19:57:06 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

int	preparing_parser(char **line, size_t *k, t_command *command)
{
	if (lexer(*line) == FAILURE_CODE)
		return (FAILURE_CODE);
	*line = ft_strdup(*line);
	command->args = (char **)ft_calloc(512, sizeof(char *));
	*k = 0;
	return (SUCCESS_CODE);
}

void	go_to_parse_next_command(t_vars *vars, char *line, size_t *k)
{
	vars->f_pipe = FALSE;
	vars->f_redir_0 = FALSE;
	vars->f_redir_1 = FALSE;
	if (line[*k] == ';')
		(*k)++;
}

void	preparing_new_command(char *line, size_t *k, t_command *command)
{
	while (line[*k] == ' ')
		(*k)++;
	command->argc = 0;
}

int	checking_end(char *line, size_t *k, size_t *argc)
{
	if (line[*k] == ' ')
	{
		(*argc)++;
		while (line[*k] == ' ')
			(*k)++;
		if (line[*k] == ';' || line[*k] == '\0')
		{
			(*argc)--;
			return (FAILURE_CODE);
		}
	}
	if (line[*k] == ';' || line[*k] == '\0')
		return (FAILURE_CODE);
	return (SUCCESS_CODE);
}

int	parsing_0(char *line, size_t *k, t_vars *vars, t_command *command)
{
	if (ft_find_in("><|", line[*k]) == TRUE)
	{
		if (parsing_1(line, k, vars, command) == FAILURE_CODE)
			return (FAILURE_CODE);
		else
			return (SUCCESS_CODE);
	}
	else if (ft_find_in("\'\"\\$", line[*k]) == TRUE)
		parsing_2(line, k, vars, command);
	else
		parsing_3(line, k, vars, command);
	if (checking_end(line, k, &command->argc) == FAILURE_CODE)
		return (SUCCESS_CODE);
}
