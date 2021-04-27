/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_if_quote_one.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 22:42:50 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/27 18:59:04 by dwinky           ###   ########.fr       */
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
		ch = char_convert_to_str(line[*k]);
		quote_line = ft_strjoin_free(quote_line, ch, 3);
		(*k)++;
	}
	return (quote_line);
}
