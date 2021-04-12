/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntactic_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 21:45:04 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/12 22:33:07 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

int	print_error(char *error)
{
	ft_putstr_fd(error, 1);
	return (1);
}

int	syntactic_parsing(char *line)
{
	int k;
	char	flag_semicolon;
	char	*tmp;

	flag_semicolon = FALSE;
	k = 0;
	if (line[k] == ';' && line[k + 1] == ';')
		return (print_error("bash: syntax error near unexpected token `;;'\n"));
	else if (line[k] == ';')
		return (print_error("bash: syntax error near unexpected token `;'\n"));
	while (line[k])
	{
		while (line[k] == ' ')
			k++;
		if (line[k] == ';')
		{
			k++;
			if (flag_semicolon == FALSE)
				flag_semicolon = TRUE;
			else
				return (print_error("bash: syntax error near unexpected token `;'\n"));
			if (line[k] == ';')
				return (print_error("bash: syntax error near unexpected token `;;'\n"));
		}
		else
			flag_semicolon = FALSE;
		k++;
	}
	k = 0;
	tmp = "";
	char *redir;

	redir = NULL;
	while (line[k])
	{
		if (line[k] == '>')
		{
			if (line[k + 1] == '>' && line[k + 2] != '>')
				redir = ">>";
			else if (line[k + 1] == '>' && line[k + 2] == '>' && line[k + 3] != '>')
				return (print_error("bash: syntax error near unexpected token `>'\n"));
			else if (line[k + 1] == '>' && line[k + 2] == '>' && line[k + 3] == '>')
				return (print_error("bash: syntax error near unexpected token `>>'\n"));
			else
				redir = ">";
			k += ft_strlen(redir);
			while (line[k] == ' ')
				k++;
			if (line[k] == '>' && line[k + 1] == '>')
				return (print_error("bash: syntax error near unexpected token `>>'\n"));
			else if (line[k] == '>')
				return (print_error("bash: syntax error near unexpected token `>'\n"));
		}
		k++;
	}
	k = 0;
	while (line[k])
	{
		k++;
	}
	return (0);
}


// " ' "        " ' "