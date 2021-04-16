/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:58:51 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/16 21:41:23 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
Одиночные кавычки (' ') схожи по своему действию с двойными кавычками, только не допускают обращение к переменным, поскольку специальный символ "$" внутри одинарных кавычек воспринимается как обычный символ.
Внутри одиночных кавычек, любой специальный символ, за исключением ', интерпретируется как простой символ.
Одиночные кавычки ("строгие, или полные кавычки") следует рассматривать как более строгий вариант чем двойные кавычки ("нестрогие, или неполные кавычки").
Поскольку внутри одиночных кавычек даже экранирующий (\) символ воспринимается как обычный символ, попытка вывести одиночную кавычку внутри строки, ограниченной одинарными кавычками,
**/
#include "head_minishell.h"

void	free_command(t_command *cmd)
{
	int k;

	k = 0;
	while (cmd->args[k])
	{
		free(cmd->args[k]);
		cmd->args[k] = 0;
		k++;
    }
}

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

char	*parse_if_quote_one(char *line, size_t *k)
{
	char *quote_line; // кавычка

	quote_line = "";
	(*k)++;
	while (line[*k] != '\'')
	{
		if (line[*k] == '\0')
			return (NULL);
		char buf[2];
		buf[0] = line[*k];
		buf[1] = 0;
		quote_line = ft_strjoin(quote_line, buf);
		(*k)++;
	}
	return (quote_line);
}

int	parser(char *line, t_vars *vars)
{
	t_command	command;
	size_t		k;
	size_t		argc;
	size_t		count;

	if (line == NULL)
		return (-1);
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
			if (line[k] == '\'')
			{
				char *quote_str = parse_if_quote_one(line, &k);
				if (quote_str == NULL)
					return (-1);
				// ft_putline("command.args[argc] >", command.args[argc], "|\n");
				if (command.args[argc] == NULL)
					command.args[argc] = ft_strdup(quote_str);
				else
					command.args[argc] = ft_strjoin(command.args[argc], ft_strdup(quote_str));
				// ft_putline_nbr("argc >", argc);
				// ft_putline("command.args[argc] >", command.args[argc], "|\n");
				k++;
				if (line[k] == ' ' || line[k] == ';' || line[k] == '\0'  || line[k] == '\\')
					argc++;
			}
			else if (line[k] == '\"')
			{
				k++;
				char *quote_line; // кавычка
				quote_line = "";
				while (line[k] != '\"')
				{
					char buf[2];
					buf[0] = line[k];
					buf[1] = 0;
					command.args[argc] = "";
					if (line[k] == '$') // идёт до след $
					{
						while (line[k] == '$')
							command.args[argc] = ft_strjoin_free(command.args[argc], parse_if_dollar(line, &k, &vars->list_env), 0);
					}
					else if (line[k] == '\\')
					{
						k++;
						buf[0] = line[k];
						quote_line = ft_strjoin(quote_line, buf);
						k++;
					}
					else
					{
						quote_line = ft_strjoin(quote_line, buf);
						k++;
					}
				}
				argc++;
			}
			else if (line[k] == '$')
			{
				command.args[argc] = "";
				while (line[k] == '$')
					command.args[argc] = ft_strjoin_free(command.args[argc], parse_if_dollar(line, &k, &vars->list_env), 0);
				argc++;
			}
			else
			{
				char *start;
				start = line + k;
				while (line[k] != ' '  && line[k] != ';' && line[k] != '$' && line[k] != '\0')
					k++;
				if (command.args[argc] == NULL)
					command.args[argc] = ft_substr(start, 0, line + k - start);
				else
					command.args[argc] = ft_strjoin(command.args[argc], ft_substr(start, 0, line + k - start));
				argc++;
				while (line[k] == '$')
					command.args[argc - 1] = ft_strjoin_free(command.args[argc - 1], parse_if_dollar(line, &k, &vars->list_env), 1);
			}
			if (line[k] == ';' || line[k] == '\0')
				break ;
		}
		if (command.args[0][0] != '\0')
			processing(&command, vars);
		free_command(&command);
		if (line[k] == ';')
			k++;
	}
	free(command.args);
	free(line);
	return (0);
}
	/** Душим, мальчики: **/

// echo!2
// echo "123"'456' это один символ
// echo 'qwe'123

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