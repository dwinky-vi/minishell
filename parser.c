/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:58:51 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/15 21:30:07 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	print_command(t_command command)
{
	int fd2 = open("testing", O_CREAT | O_RDWR | O_APPEND, 0777);
	int k = 0;
	while (command.args[k])
	{
		ft_putstr_fd("k = ", fd2);
		ft_putnbr_fd(k, fd2);
		ft_putstr_fd(" >", fd2);
		ft_putstr_fd(command.args[k], fd2);
		ft_putstr_fd("|\n", fd2);
		k++;
	}
}

int	parser(char *line, t_vars *vars)
{
	t_command	command;
	size_t		k;
	size_t		argc;
	size_t		count;

	if (line == NULL)
		return (-1);
	// line = ft_strtrim(line, " "); // есть лик из-за этого
	// if (syntactic_parsing(line) == 1)
	// 	return (1);
	command.args = (char **)ft_calloc(30, sizeof(char *)); // кол-во аргументов
	k = 0;
	while (line[k])
	{
		argc = 0;
		while (line[k])
		{
			while (line[k] == ' ')
				k++;
			char *start;
			start = line + k;
			if (line[k] == '\'')
			{
				k++;
				char *quote_line; // кавычка
				quote_line = "";
				while (line[k] != '\'')
				{
					char buf[2];
					buf[0] = line[k];
					buf[1] = 0;
					quote_line = ft_strjoin(quote_line, buf);
					k++;
				}
				command.args[argc++] = ft_strdup(quote_line);
			}
			else
			{
				while (line[k] != ' ' && line[k] != '\0'  && line[k] != ';')
					k++;
				command.args[argc++] = ft_substr(start, 0, line + k - start);
			}
			if (line[k] == ';' || line[k] == '\0')
				break ;
			k++;
		}
		processing(&command, vars);
		int z = 0;
		while (command.args[z])
        {
			free(command.args[z]);
			command.args[z] = 0;
		    z++;
        }
		if (line[k] == ';')
			k++;
	}
	free(command.args);
	return (0);
}
