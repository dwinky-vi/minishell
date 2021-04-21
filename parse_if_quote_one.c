/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_if_quote_one.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 22:42:50 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/17 22:48:15 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

char	*parse_if_quote_one(char *line, size_t *k)
{
	char	*quote_line;
	char	*ch;

	quote_line = ft_strdup("");
	(*k)++;
	while (line[*k] != '\'')
	{
		if (line[*k] == '\0')
		{
			free(quote_line);
			return (NULL);
		}
		ch = char_convert_to_str(line[*k]);
		if (ch == NULL)
		{
			free(quote_line);
			return (NULL);
		}
		quote_line = ft_strjoin_free(quote_line, ch, 3);
		if (quote_line == NULL)
			return (NULL);
		(*k)++;
	}
	return (quote_line);
}
