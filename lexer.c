/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 21:45:04 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/21 19:14:44 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

int	syntax_error(char *token)
{
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd("syntax error near unexpected token `", 1);
	ft_putstr_fd(token, 1);
	ft_putstr_fd("'\n", 1);
	return (1);
}

int	lexer(char *line)
{
	size_t	k;

	k = 0;
	if (line[k] == ';' && line[k + 1] == ';')
		return (syntax_error(";;"));
	else if (line[k] == ';')
		return (syntax_error(";"));
	while (line[k])
	{
		if (line[k] == '\\')
		{
			if (line[k + 1] == '\0')
				return (syntax_error("\\"));
			k += 2;
		}
		if (line[k] == '\"')
		{
			k++;
			while (line[k] != '\"')
			{
				if (line[k] == '\\')
					k++;
				if (line[k] == '\0')
					return (syntax_error("\""));
				k++;
			}
		}
		if (line[k] == '\'')
		{
			k++;
			while (line[k] && line[k] != '\'')
				k++;
			if (line[k] == '\0')
				return (syntax_error("\'"));
		}
		// if (line[k] == '|')
		// {
		// 	if (ft_strncmp(line + k, "||||", 4))
		// 	{
		// 		return (print_error("bash: syntax error near unexpected token `||'"));
		// 	}
		// 	k++;
		// 	if (line[k] == '|')
		// 		return (print_error("bash: syntax error near unexpected token `||'"));
		// 	while (line[k] == ' ')
		// 		k++;
		// 	if (line[k] == '\0' || line[k] == ';')
		// 		return (print_error("bash: syntax error near unexpected token `|'"));
		// }
		if (line[k] == ';')
		{
			if (line [k + 1] == ';')
				return (syntax_error(";;"));
			k++;
			while (line[k] == ' ')
				k++;
			if (line[k] == ';' && line[k + 1] == ';')
				return (syntax_error(";;"));
			else if (line[k] == ';')
				return (syntax_error(";"));
		}
		k++;
	}
	return (0);
}


// int	lexer(char *line)
// {
// 	int k;

// 	k = 0;
// 	if (line[k] == 34) // 34 == "
// 	{
// 		while (line[++k] != 34 && line[k])
// 			k++;
// 		if (line[k] == '\0')
// 			return (print_error("bash: syntax error near unexpected token `\"'\n"));
// 	}
// 	else if (line[k] == 39) // 39 == '
// 	{
// 		while (line[++k] != 39 && line[k])
// 			k++;
// 		if (line[k] == '\0')
// 			return (print_error("bash: syntax error near unexpected token `\''\n"));
// 	}
// 	else if (line[k] == 92) // 92 == \ //
// 	{
// 		k += 2;
// 	}
// 	else if (line[k] == '>')
// 	{
// 		char *redir;

// 		redir = NULL;
// 		if (line[k + 1] == '>' && line[k + 2] != '>')
// 			redir = ">>";
// 		else if (line[k + 1] == '>' && line[k + 2] == '>' && line[k + 3] != '>')
// 			return (print_error("bash: syntax error near unexpected token `>'\n"));
// 		else if (line[k + 1] == '>' && line[k + 2] == '>' && line[k + 3] == '>')
// 			return (print_error("bash: syntax error near unexpected token `>>'\n"));
// 		else
// 			redir = ">";
// 		k += ft_strlen(redir);
// 		while (line[k] == ' ')
// 			k++;
// 		if (line[k] == '>' && line[k + 1] == '>')
// 			return (print_error("bash: syntax error near unexpected token `>>'\n"));
// 		else if (line[k] == '>')
// 			return (print_error("bash: syntax error near unexpected token `>'\n"));
// 	}
// 	else
// 	{
// 		k++;
// 		// ft_putline("|", line, "|");
// 	}
// 	return (0);
// }
