/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 19:31:09 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/27 21:02:33 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

int	lexing_begin_line(char *line, size_t k)
{
	if (line[k] == ';' && line[k + 1] == ';')
		return (syntax_error(";;"));
	else if (line[k] == ';')
		return (syntax_error(";"));
	if (line[k] == '|' && line[k + 1] == '|')
		return (syntax_error("||"));
	else if (line[k] == '|')
		return (syntax_error("|"));
	return (SUCCESS_CODE);
}

int	lexing_special_character(char *line, size_t *k)
{
	if (line[*k] == '\\')
	{
		if (lexer_shielding(line, k) == FAILURE_CODE)
			return (FAILURE_CODE);
	}
	else if (line[*k] == '\'' || line[*k] == '\"')
	{
		if (lexer_quote(line, k) == FAILURE_CODE)
			return (FAILURE_CODE);
	}
	else if (line[*k] == '|' || line[*k] == '>' || line[*k] == '<')
	{
		if (lexer_pipe_or_redir(line, k) == FAILURE_CODE)
			return (FAILURE_CODE);
	}
	else if (line[*k] == ';')
	{
		if (lexer_semicolon(line, k) == FAILURE_CODE)
			return (FAILURE_CODE);
	}
	return (SUCCESS_CODE);
}

int	lexer_shielding(char *line, size_t *k)
{
	(*k)++;
	if (line[*k] == '\0')
		return (syntax_error("\\"));
	(*k)++;
	return (SUCCESS_CODE);
}

int	lexer_quote(char *line, size_t *k)
{
	if (line[*k] == '\'')
	{
		(*k)++;
		while (line[*k] && line[*k] != '\'')
			(*k)++;
		if (line[*k] == '\0')
			return (syntax_error("\'"));
	}
	else
	{
		(*k)++;
		while (line[*k] != '\"')
		{
			if (line[*k] == '\\')
				(*k)++;
			if (line[*k] == '\0')
				return (syntax_error("\""));
			(*k)++;
		}
	}
	(*k)++;
	return (SUCCESS_CODE);
}

int	lexer_semicolon(char *line, size_t *k)
{
	if (line[*k + 1] == ';')
		return (syntax_error(";;"));
	(*k)++;
	while (line[*k] == ' ')
		(*k)++;
	if (line[*k] == ';' && line[*k + 1] == ';')
		return (syntax_error(";;"));
	else if (line[*k] == ';')
		return (syntax_error(";"));
	return (SUCCESS_CODE);
}
