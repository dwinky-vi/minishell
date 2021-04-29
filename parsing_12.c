/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_12.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 19:32:26 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/29 19:49:46 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

static char	*just_an_argument(char *line, size_t *k)
{
	char	*start;

	start = line + *k;
	while (!is_special_character(line[*k]) && line[*k] != '\0')
		(*k)++;
	return (ft_substr(start, 0, (line + *k) - start));
}

int	parsing_1(char *line, size_t *k, t_vars *vars, t_command *command)
{
	if (line[*k] == '|')
	{
		vars->f_pipe = TRUE;
		(*k)++;
		return (SUCCESS_CODE);
	}
	else if (line[*k] == '>')
	{
		if (parse_if_redir(line, k, vars, command) == FAILURE_CODE)
			return (FAILURE_CODE);
	}
	else if (line[*k] == '<')
	{
		if (parse_if_back_redir(line, k, vars, command) == \
															FAILURE_CODE)
			return (FAILURE_CODE);
	}
	return (SUCCESS_CODE);
}

static void	parsing_2_if_quote(char *line, size_t *k, t_vars *vars, \
														t_command *cmd)
{
	if (line[*k] == '\'')
	{
		cmd->args[cmd->argc] = ft_strjoin_free(cmd->args[cmd->argc], \
							parse_if_quote_one(line, k), 3);
		(*k)++;
	}
	else if (line[*k] == '\"')
	{
		cmd->args[cmd->argc] = ft_strjoin_free(cmd->args[cmd->argc], \
							parse_if_quote_two(line, k, vars->list_env), 3);
		(*k)++;
	}
}

void	parsing_2(char *line, size_t *k, t_vars *vars, t_command *cmd)
{
	if (cmd->args[cmd->argc] == NULL)
		cmd->args[cmd->argc] = ft_strdup("");
	if (line[*k] == '\"' || line[*k] == '\"')
	{
		parsing_2_if_quote(line, k, vars, cmd);
	}
	else if (line[*k] == '\\')
	{
		cmd->args[cmd->argc] = ft_strjoin_free(cmd->args[cmd->argc], \
												char_to_str(line[*k + 1]), 3);
		(*k) += 2;
	}
	else if (line[*k] == '$' && (line[*k + 1] == '\'' || line[*k + 1] == '\"'))
	{
		(*k)++;
	}
	else if (line[*k] == '$')
	{
		while (line[*k] == '$')
			cmd->args[cmd->argc] = ft_strjoin_free(cmd->args[cmd->argc], \
								parse_if_dollar(line, k, &vars->list_env), 3);
	}
}

void	parsing_3(char *line, size_t *k, t_vars *vars, t_command *cmd)
{
	if (cmd->args[cmd->argc] == NULL)
		cmd->args[cmd->argc] = ft_strdup("");
	cmd->args[cmd->argc] = ft_strjoin_free(cmd->args[cmd->argc], \
											just_an_argument(line, &k), 3);
}
