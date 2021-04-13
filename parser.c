/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:58:51 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/13 19:13:55 by dwinky           ###   ########.fr       */
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
int	parser(char *line, t_list *list_env, char **envp)
{
	t_command	command;
	size_t		k;
	size_t		argc;
	size_t		count;

	if (line == NULL)
		return (-1);
	line = ft_strtrim(line, " "); // !!!!!!!!!
	if (syntactic_parsing(line) == 1)
		return (1);
	k = 0;
	// while (*line == ' ')                                                         //
	// 	line++;                                                         //
	// k = 0;                                                         //
	// while (line[k] != ' ' && line[k])                                                         //
	// 	k++;                                                         //
	// command.name = ft_substr(line, 0, k);                                                         //
	// line += k;                                                         //
	// k = 0;                                                         //
	command.args = (char **)ft_calloc(30, sizeof(char *)); // кол-во аргументов
	// count = 0;
	// while (*line)
	// {
	// 	while (*line == ' ')
	// 		line++;
	// 	k = 0;
	// 	while (line[k] != ' ' && line[k])
	// 		k++;
	// 	command.args[count++] = ft_substr(line, 0, k);
	// 	line += k;
	// }
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
			while (line[k] != ' ' && line[k] != '\0'  && line[k] != ';')
				k++;
			command.args[argc++] = ft_substr(start, 0, line + k - start);
			if (line[k] == ';' || line[k] == '\0')
				break ;
			k++;
		}
		k++;
		print_command(command);
		// processing(&command, &list_env, envp);
		k = 0;
		while (command.args[k])
        {
            ft_bzero(command.args + k, sizeof(char **));
		    k++;
        }
//		command.args[0] = 0;
//		command.args[1] = 0;
//		command.args[2] = 0;
//		command.args[3] = 0;
//		command.args[4] = 0;
//		command.args[5] = 0;
	}
	k = 0;

	return (0);
}
