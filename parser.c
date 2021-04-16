/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:58:51 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/16 13:09:32 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
Одиночные кавычки (' ') схожи по своему действию с двойными кавычками, только не допускают обращение к переменным, поскольку специальный символ "$" внутри одинарных кавычек воспринимается как обычный символ.
Внутри одиночных кавычек, любой специальный символ, за исключением ', интерпретируется как простой символ.
Одиночные кавычки ("строгие, или полные кавычки") следует рассматривать как более строгий вариант чем двойные кавычки ("нестрогие, или неполные кавычки").
Поскольку внутри одиночных кавычек даже экранирующий (\) символ воспринимается как обычный символ, попытка вывести одиночную кавычку внутри строки, ограниченной одинарными кавычками,
**/
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
			// else if (line[k] == '\"')
			// {
			// 	k++;
			// 	char *quote_line; // кавычка
			// 	quote_line = "";
			// 	while (line[k] != '\"')
			// 	{
			// 		char buf[2];
			// 		buf[0] = line[k];
			// 		buf[1] = 0;
			// 		if (line[k] == '$') // идёт до след $
			// 		{
			// 			k++;
			// 			int k2 = k;
			// 			char *buf2;
			// 			while (line[k2] != ' ' && line[k2] != '$')
			// 			{
			// 				k2++;
			// 			}
			// 			buf2 = (char *)ft_calloc(k2 - k, 1);
			// 		}
			// 		else if (line[k] == '\\')
			// 		{
			// 			k++;
			// 		}
			// 		quote_line = ft_strjoin(quote_line, buf);
			// 		k++;
			// 	}
			// 	command.args[argc++] = ft_strdup(quote_line);
			// }
			else if (line[k] == '$')
			{
				k++;
				int kk = k;
				while (line[kk] != ' ' && line[kk] != '$' && line[kk] != '\'' && line[kk] != '\"' && line[kk] != '\\')
				{
					kk++;
				}
				char *key = ft_substr(line, k, kk - k);
				ft_putline("key >", key, "|");
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

// echo!2
// echo "123"'456' это один символ
// Символ "!", помещенный в двойные кавычки, порождает сообщение об ошибке, если команда вводится с командной строки.
// Вероятно это связано с тем, что этот символ интерпретируется как попытка обращения к истории команд.
// Однако внутри сценариев такой прием проблем не вызывает.

/** ' одиночная кавычка
 * экранирование не работает, переменные окружения тоже.
 * любой символ интерпретируется как обычный символ
**/

/** " двойная кавычка
 * экранирование работает
 * переменные окружения работают
 * 
**/

/** $ переменные окружения
 * парсятся до спец символа ($ \ " ' )
**/