/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:58:51 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/13 05:35:01 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

int	parser(char *line, t_list *list_env, char **envp)
{
	t_command	command;
	size_t		k;
	size_t		count;

	if (line == NULL)
		return (-1);
	command.args = (char **)ft_calloc(20, sizeof(char *)); // кол-во аргументов
	count = 0;
	while (*line)
	{
		while (*line == ' ')
			line++;
		k = 0;
		while (line[k] != ' ' && line[k])
			k++;
		command.args[count++] = ft_substr(line, 0, k);
		line += k;
	}
	processing(&command, &list_env, envp);
	return (0);
}
