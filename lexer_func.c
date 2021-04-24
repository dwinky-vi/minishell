/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 19:31:09 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/25 01:21:48 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

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
	if (line[*k] == '\"')
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
	else
	{
		(*k)++;
		while (line[*k] && line[*k] != '\'')
			(*k)++;
		if (line[*k] == '\0')
			return (syntax_error("\'"));
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
