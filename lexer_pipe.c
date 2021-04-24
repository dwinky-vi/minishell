/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 18:54:30 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/24 19:59:50 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

int	lexer_pipe(char *line, size_t *k)
{
	int	tmp;
	int	f;

	f = FALSE;
	tmp = *k - 1;
	while (line[tmp] == ' ' && tmp > 0)
		tmp--;
	if (ft_isalpha(line[tmp]) || ft_isdigit(line[tmp]))
		f = TRUE;
	(*k)++;
	while (line[*k] == ' ')
		(*k)++;
	if (line[*k] == ';' && f == TRUE)
		return (syntax_error(";"));
	else if (line[*k] == '|' || line[*k] == ';' || line[*k] == '\0')
		return (syntax_error("|"));
	return (SUCCESS_CODE);
}
