/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:58:51 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/28 20:44:55 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	free_command(t_command *cmd)
{
	int k;

	k = 0;
	while (cmd->args[k])
	{
		free(cmd->args[k]);
		cmd->args[k] = 0;
		k++;
    }
}

char	*just_an_argument(char *line, size_t *k)
{
	char *start;

	start = line + *k;
	while (!is_special_character(line[*k]) && line[*k] != '\0')
		(*k)++;
	return (ft_substr(start, 0, (line + *k) - start));
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

int	parser(char *line, t_vars *vars)
{
	t_command	command;
	size_t		k;
	size_t		argc;

	if (lexer(line) == FAILURE_CODE)
		return (FAILURE_CODE);
	line = ft_strdup(line);
	command.args = (char **)ft_calloc(512, sizeof(char *)); // кол-во аргументов
	k = 0;
	while (line[k])
	{
		while (line[k] == ' ')
			k++;
		argc = 0;
		while (line[k])
		{
			if (line[k] == '\'')
			{
				if (command.args[argc] == NULL)
					command.args[argc] = ft_strdup("");
				command.args[argc] = ft_strjoin_free(command.args[argc], parse_if_quote_one(line, &k), 3);
				k++;
			}
			else if (line[k] == '\"')
			{
				if (command.args[argc] == NULL)
					command.args[argc] = ft_strdup("");
				command.args[argc] = ft_strjoin_free(command.args[argc], parse_if_quote_two(line, &k, vars->list_env), 3);
				k++;
			}
			else if (line[k] == '\\')
			{
				if (command.args[argc] == NULL)
					command.args[argc] = ft_strdup("");
				command.args[argc] = ft_strjoin_free(command.args[argc], char_convert_to_str(line[k + 1]), 3);
				k += 2;
			}
			else if (line[k] == '$')
			{
				if (command.args[argc] == NULL)
					command.args[argc] = ft_strdup("");
				while (line[k] == '$')
					command.args[argc] = ft_strjoin_free(command.args[argc], parse_if_dollar(line, &k, &vars->list_env), 3);
				if (command.args[argc][0] == '\0')
				{
					free(command.args[argc]);
					command.args[argc] = NULL;
				}
			}
			else if (line[k] == '|')
			{
				vars->f_pipe = TRUE;
				k++;
				break ;
			}
			else if (line[k] == '>')
			{
				if (parse_if_redir(line, &k, vars, &command) == FAILURE_CODE)
					return (FAILURE_CODE);
			}
			else if (line[k] == '<')
			{
				if (parse_if_back_redir(vars, &command, line, &k) == FAILURE_CODE)
					return (FAILURE_CODE);
			}
			else
			{
				if (command.args[argc] == NULL)
					command.args[argc] = ft_strdup("");
				command.args[argc] = ft_strjoin_free(command.args[argc], just_an_argument(line, &k), 3);
			}
			if (checking_end(line, &k, &argc) == FAILURE_CODE)
				break ;
		}
		preprocessing(&command, vars);
		if (line[k] == ';')
			k++;
	}
	free(command.args);
	free(line);
	return (SUCCESS_CODE);
}
