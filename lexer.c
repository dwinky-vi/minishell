/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 21:45:04 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/25 03:10:16 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

int	lexer(char *line)
{
	size_t	k;

	k = 0;
	// if (line[k] == ';' && line[k + 1] != ';')
	// 	return (syntax_error(";"));
	if (line[k] == ';' && line[k + 1] == ';')
		return (syntax_error(";;"));
	else if (line[k] == ';')
		return (syntax_error(";"));
	while (line[k])
	{
		if (line[k] == '\\')
		{
			if (lexer_shielding(line, &k) == FAILURE_CODE)
				return (FAILURE_CODE);
		}
		else if (line[k] == '\'' || line[k] == '\"')
		{
			if (lexer_quote(line, &k) == FAILURE_CODE)
				return (FAILURE_CODE);
		}
		else if (line[k] == '|')
		{
			if (lexer_pipe(line, &k) == FAILURE_CODE)
				return (FAILURE_CODE);
		}
		else if (line[k] == '>')
		{
			if (lexer_right_redir(line, &k) == FAILURE_CODE)
				return (FAILURE_CODE);
		}
		else if (line[k] == '<')
		{
			if (lexer_left_redir(line, &k) == FAILURE_CODE)
				return (FAILURE_CODE);
		}
		else if (line[k] == ';')
		{
			if (lexer_semicolon(line, &k) == FAILURE_CODE)
				return (FAILURE_CODE);
		}
		else
			k++;
	}
	return (0);
}
