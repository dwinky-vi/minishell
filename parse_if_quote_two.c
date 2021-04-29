/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_if_quote_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:13:15 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/29 04:43:27 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

char	*parse_if_quote_two(char *line, size_t *k, t_list *list_env)
{
	char	*quote;

	(*k)++;
	quote = ft_strdup("");
	while (line[*k] != '\"')
	{
		if (line[*k] == '$')
		{
			while (line[*k] == '$')
				quote = ft_strjoin_free(quote, \
									parse_if_dollar(line, k, &list_env), 3);
		}
		else if (line[*k] == '\\' && (ft_find_in("\\$\"", line[*k + 1])))
		{
			quote = ft_strjoin_free(quote, char_to_str(line[*k + 1]), 3);
			(*k) += 2;
		}
		else
		{
			quote = ft_strjoin_free(quote, char_to_str(line[*k]), 3);
			(*k)++;
		}
	}
	return (quote);
}
