/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntactic_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 21:45:04 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/10 22:10:57 by dwinky           ###   ########.fr       */
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

	k = 0;
	while (line[k])
	{
		while (line[k] == ' ')
			k++;
		if (ft_strncmp(line + k, ";;", 2) == 0)
			return (print_error("bash: syntax error near unexpected token `;;'\n"));

		k++;
	}
	return (0);
}