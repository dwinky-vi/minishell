/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_if_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:07:20 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/29 01:43:49 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	quote_mini(char *line, size_t *k, char **file, t_list *lst_env)
{
	if (line[*k] == '\'')
	{
		*file = ft_strjoin_free(*file, parse_if_quote_one(line, k), 3);
		(*k)++;
	}
	else if (line[*k] == '\"')
	{
		*file = ft_strjoin_free(*file, parse_if_quote_two(line, k, lst_env), 3);
		(*k)++;
	}
}

void	get_file_name(char *line, size_t *k, t_vars *vars, char **file)
{
	*file = ft_strdup("");
	while (ft_find_in(" ;|><", line[*k]) == FALSE && line[*k] != '\0')
	{
		if (line[*k] == '\'' || line[*k] == '\"')
		{
			quote_mini(line, k, file, vars->list_env);
		}
		else if (line[*k] == '\\')
		{
			*file = ft_strjoin_free(*file, \
										char_convert_to_str(line[*k + 1]), 3);
			*k += 2;
		}
		else if (line[*k] == '$')
		{
			while (line[*k] == '$')
				*file = ft_strjoin_free(*file, \
								parse_if_dollar(line, k, &vars->list_env), 3);
		}
		else
		{
			*file = ft_strjoin_free(*file, char_convert_to_str(line[*k]), 3);
			(*k)++;
		}
	}
}

int	parsing_if_redir(char *line, size_t *k, t_vars *vars, t_command *command)
{
	char	*file;

	if (line[*k] == '>' && line[*k + 1] == '>')
	{
		*k += 2;
		while (line[*k] == ' ')
			(*k)++;
		get_file_name(line, k, vars, &file);
		command->fd[1] = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	}
	else if (line[*k] == '>')
	{
		(*k)++;
		while (line[*k] == ' ')
			(*k)++;
		get_file_name(line, k, vars, &file);
		command->fd[1] = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	if (command->fd[1] == -1)
		return (redir_error(vars, command, file));
	free(file);
	return (SUCCESS_CODE);
}

int	parse_if_redir(char *line, size_t *k, t_vars *vars, t_command *command)
{
	if (vars->f_redir_1 == TRUE)
		close(command->fd[1]);
	vars->f_redir_1 = TRUE;
	if (parsing_if_redir(line, k, vars, command) == FAILURE_CODE)
		return (FAILURE_CODE);
	dup2(command->fd[1], 1);
	while (line[*k] == ' ')
		(*k)++;
	return (SUCCESS_CODE);
}
