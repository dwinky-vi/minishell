/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 21:45:04 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/27 21:44:43 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

int	lexer(char *line)
{
	size_t	k;

	k = 0;
	if (lexing_begin_line(line, k) == FAILURE_CODE)
		return (FAILURE_CODE);
	while (line[k])
	{
		if (ft_find_in("\'\"\\|><;", line[k]) == TRUE)
		{
			if (lexing_special_character(line, &k) == FAILURE_CODE)
				return (FAILURE_CODE);
		}
		else
			k++;
	}
	return (0);
}
