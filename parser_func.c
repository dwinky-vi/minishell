/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 17:18:45 by dwinky            #+#    #+#             */
/*   Updated: 2021/06/29 19:09:22 by dwinky           ###   ########.fr       */
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
			return (BREAK_CODE);
		}
	}
	if (line[*k] == ';' || line[*k] == '\0')
		return (BREAK_CODE);
	return (SUCCESS_CODE);
}

int	parsing_0(char *line, size_t *k, t_vars *vars, t_command *command)
{
	int	r;

	if (ft_find_in("><|", line[*k]) == TRUE)
	{
		r = parsing_1(line, k, vars, command);
		if (r == FAILURE_CODE)
			return (FAILURE_CODE);
		else if (r == BREAK_CODE)
			return (BREAK_CODE);
	}
	else if (ft_find_in("\'\"\\$", line[*k]) == TRUE)
		parsing_2(line, k, vars, command);
	else
		parsing_3(line, k, command);
	if (checking_end(line, k, &command->argc) == BREAK_CODE)
		return (BREAK_CODE);
	return (SUCCESS_CODE);
}
