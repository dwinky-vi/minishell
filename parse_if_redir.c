/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_if_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:07:20 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/28 20:34:09 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

char	*get_file_name(char *line, size_t *k, t_vars *vars)
{
	char	*file_name;

	file_name = ft_strdup("");
	while (line[*k] != ' ' && line[*k] != ';' && line[*k] != '|' && line[*k] != '>' && line[*k] != '<' && line[*k] != '\0')
	{
		if (line[*k] == '\'')
		{
			file_name = ft_strjoin_free(file_name, parse_if_quote_one(line, k), 3);
			(*k)++;
		}
		else if (line[*k] == '\"')
		{
			file_name = ft_strjoin_free(file_name, parse_if_quote_two(line, k, vars->list_env), 3);
			(*k)++;
		}
		else if (line[*k] == '\\')
		{
			file_name = ft_strjoin_free(file_name, char_convert_to_str(line[*k + 1]), 3);
			*k += 2;
		}
		else if (line[*k] == '$')
		{
			while (line[*k] == '$')
				file_name = ft_strjoin_free(file_name, parse_if_dollar(line, k, &vars->list_env), 3);
		}
		else
		{
			file_name = ft_strjoin_free(file_name, char_convert_to_str(line[*k]), 3);
			(*k)++;
		}
	}
	return (file_name);
}

int	parsing_if_redir(char *line, size_t *k, t_vars *vars)
{
	char *file_name;

	if (line[*k] == '>' && line[*k + 1] == '>')
	{
		*k += 2;
		while (line[*k] == ' ')
			(*k)++;
		file_name = get_file_name(line, k, vars);
		command->fd[1] = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
	}
	else if (line[*k] == '>')
	{
		(*k)++;
		while (line[*k] == ' ')
			(*k)++;
		file_name = get_file_name(line, k, vars);
		command->fd[1] = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	if (command->fd[1] == -1)
		return (redir_error(vars, command, file_name));
	free(file_name);
	return (SUCCESS_CODE);
}

int	parse_if_redir(char *line, size_t *k, t_vars *vars, t_command *command)
{
	if (vars->f_redir_1 == TRUE)
		close(command->fd[1]);
	vars->f_redir_1 = TRUE;
	if (parsing_if_redir(line, k, vars) == FAILURE_CODE)
		return (FAILURE_CODE);
	dup2(command->fd[1], 1);
	while (line[*k] == ' ')
		(*k)++;
	return (SUCCESS_CODE);
}