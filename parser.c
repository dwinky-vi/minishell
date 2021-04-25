/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:58:51 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/25 06:02:18 by aquinoa          ###   ########.fr       */
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

int	parser(char *line, t_vars *vars)
{
	t_command	command;
	size_t		k;
	size_t		argc;
	size_t		count;

	if (line == NULL)
		return (FAILURE_CODE);
	if (lexer(line) == FAILURE_CODE)
	{
		free(line);
		return (FAILURE_CODE);
	}
	command.args = (char **)ft_calloc(512, sizeof(char *)); // кол-во аргументов
	k = 0;
	while (line[k])
	{
		while (line[k] == ' ')
			k++;
		argc = 0;
		while (line[k])
		{
			if (line[k] == '\'')
			{
				char *quote_str = parse_if_quote_one(line, &k);
				if (quote_str == NULL)
					return (FAILURE_CODE);
				if (command.args[argc] == NULL)
					command.args[argc] = ft_strdup(quote_str);
				else
					command.args[argc] = ft_strjoin_free(command.args[argc], ft_strdup(quote_str), 3);
				free(quote_str);
				k++;
			}
			else if (line[k] == '\"')
			{
				k++;
				// char *quote_line;
				// quote_line = ft_strdup("");
				if (command.args[argc] == NULL)
					command.args[argc] = ft_strdup("");
				while (line[k] != '\"')
				{
					if (line[k] == '$') // идёт до след $
					{
						while (line[k] == '$')
							command.args[argc] = ft_strjoin_free(command.args[argc], parse_if_dollar(line, &k, &vars->list_env), 3);
					}
					else if (line[k] == '\\' && (line[k + 1] == '$' || line[k + 1] == '\\' || line[k + 1] == '\"'))
					{
						k++;
						command.args[argc] = ft_strjoin_free(command.args[argc], char_convert_to_str(line[k]), 3);
						k++;
					}
					else
					{
						command.args[argc] = ft_strjoin_free(command.args[argc], char_convert_to_str(line[k]), 3);
						k++;
					}
				}
				k++;
				// command.args[argc] = ft_strjoin_free(command.args[argc], quote_line, 3);
			}
			else if (line[k] == '\\')
			{
				k++;
				if (command.args[argc] == NULL)
					command.args[argc] = ft_strdup("");
				command.args[argc] = ft_strjoin_free(command.args[argc], char_convert_to_str(line[k]), 3);
				k++;
			}
			else if (line[k] == '$')
			{
				if (command.args[argc] == NULL)
					command.args[argc] = ft_strdup("");
				if (ft_isdigit(line[k + 1]))
				{
					k += 2;
					continue ;
				}
				while (line[k] == '$')
					command.args[argc] = ft_strjoin_free(command.args[argc], parse_if_dollar(line, &k, &vars->list_env), 3);
				if (command.args[argc][0] == '\0')
				{
					free(command.args[argc]);
					command.args[argc] = NULL; // and free()!!!!!!!!!!!
				}
			}
			else if (line[k] == '#') // комментарий, это опционально
			{
				line[k] = '\0';
				break ;
			}
			else if (line[k] == '|') // комментарий, это опционально
			{
				vars->f_pipe = TRUE;
				k++;
				break ;
			}
			else if (line[k] == '>')
			{
				vars->f_redir = TRUE;
				char *file_name;
				if (line[k] == '>' && line[k + 1] == '>')
				{
					k += 2;
					while (line[k] == ' ')
						k++;
					int start = k;
					while (line[k] != ' ' && line[k] != ';' && line[k] != '\0')
						k++;
					file_name = ft_substr(line, start, k - start);
					command.fd[1] = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
					free(file_name);
				}
				else if (line[k] == '>')
				{
					k++;
					while (line[k] == ' ')
						k++;
					int start = k;
					while (line[k] != ' ' && line[k] != ';' && line[k] != '\0')
						k++;
					file_name = ft_substr(line, start, k - start);
					command.fd[1] = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
					free(file_name);
				}
				dup2(command.fd[1], 1); //				!!! Заменяю fd для записи в файл !!!
				while (line[k] == ' ')
					k++;
			}
			else if (line[k] == '<')
			{
				// https://zalinux.ru/?p=3934#8
				vars->f_redir = TRUE;
				k++;
				if (line[k] == '>')
				{
					continue ;
				}
				char *file_name;
				while (line[k] == ' ')
					k++;
				int start = k;
				while (line[k] != ' ' && line[k] != ';' && line[k] != '\0')
					k++;
				file_name = ft_substr(line, start, k - start);
				command.fd[0] = open(file_name,  O_RDWR, 0644);
				free(file_name);
				dup2(command.fd[0], 0); //				!!! Заменяю fd для чтения с файла !!!
				while (line[k] == ' ')
					k++;
			}
			else // это обычный аргумент, без каких-то спец символов
			{
				char *start;
				start = line + k;
				while (line[k] != ' ' && line[k] != ';' && line[k] != '\\'  && line[k] != '\'' && line[k] != '\"' && line[k] != '$' && line[k] != '|' && line[k] != '\0')
					k++;
				if (command.args[argc] == NULL)
					command.args[argc] = ft_substr(start, 0, line + k - start);
				else
					command.args[argc] = ft_strjoin_free(command.args[argc], ft_substr(start, 0, line + k - start), 3);
			}
			// if (line[k] == ' ')
			// 	argc++;
			// while (line[k] == ' ')
				// k++;
			if (line[k] == ' ')
			{
				argc++;
				while (line[k] == ' ')
					k++;
				if (line[k] == ';' || line[k] == '\0')
				{
					argc--;
					break ;
				}
			}
			if (line[k] == ';' || line[k] == '\0')
				break ;
		}
		preprocessing(&command, vars);
		free_command(&command);
		if (line[k] == ';')
			k++;
	}
	free(command.args);
	free(line);
	return (SUCCESS_CODE);
}

// Символ "!", помещенный в двойные кавычки, порождает сообщение об ошибке, если команда вводится с командной строки.
// Вероятно это связано с тем, что этот символ интерпретируется как попытка обращения к истории команд.
// Однако внутри сценариев такой прием проблем не вызывает.

/** ' одиночная кавычка
 * экранирование не работает, переменные окружения тоже.
 * любой символ интерпретируется как обычный символ
 * Одинарные кавычки не могут находиться в одинарных кавычках.
**/

/** " двойная кавычка
 * только $ и \
 *
Обратная косая черта должна сохранять свое особое значение как escape-символ (см. Escape-символ ( обратная косая черта ) ) только тогда, когда за ней следует один из следующих символов, если они считаются специальными:
$ `" \ <новая строка>
**/

/** $ переменные окружения
 * парсятся до спец символа ($ \ " ' )
**/

// Обратная косая черта, которая не заключена в кавычки, должна сохранять буквальное значение следующего символа, за исключением <новой строки>.
// Если за обратной косой чертой следует <новая строка>, оболочка интерпретирует это как продолжение строки.
// Обратная косая черта и <новая строка> должны быть удалены перед разделением ввода на токены.
// Поскольку экранированная <новая строка> полностью удаляется из ввода и не заменяется пробелами, она не может служить разделителем токенов.