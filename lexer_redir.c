/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:43:56 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/27 21:14:01 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

		/** '>' '>>' */
int	lexer_right_redir(char *line, size_t *k)
{
	if (!ft_strncmp(line + *k, ">>>>", 4))
		return (syntax_error(">>"));
	if (!ft_strncmp(line, ">>>|", 4))
		return (syntax_error(">|"));
	if (!ft_strncmp(line + *k, ">>>", 3))
		return (syntax_error(">"));
	while (line[*k] == '>')
		(*k)++;
	while (line[*k] == ' ')
		(*k)++;
	if (line[*k] == '>' && line[*k + 1] == '>')
		return (syntax_error(">>"));
	if (line[*k] == '<')
		return (syntax_error("<"));
	if (line[*k] == '>' )
		return (syntax_error(">"));
	if (line[*k] == '|' )
		return (syntax_error("|"));
	if (line[*k] == ';' && line[*k + 1] == ';')
		return (syntax_error(";;"));
	if (line[*k] == ';')
		return (syntax_error(";"));
	if (line[*k] == '\0')
		return (syntax_error("newline"));
	return (SUCCESS_CODE);
}

		/** only '<' */
int	lexer_left_redir(char *line, size_t *k)
{
	(*k)++;
	while (line[*k] == ' ')
		(*k)++;
	if (line[*k] == '<')
		return (syntax_error("<"));
	if (line[*k] == '>' && line[*k + 1] == '>')
		return (syntax_error(">>"));
	if (line[*k] == '>' )
		return (syntax_error(">"));
	if (line[*k] == ';' && line[*k + 1] == ';')
		return (syntax_error(";;"));
	if (line[*k] == ';')
		return (syntax_error(";"));
	if (line[*k] == '\0')
		return (syntax_error("newline"));
	return (SUCCESS_CODE);
}
