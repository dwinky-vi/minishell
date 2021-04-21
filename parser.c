/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:58:51 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/21 19:38:58 by aquinoa          ###   ########.fr       */
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
		return (-1);
	if (lexer(line))
		return (1);
	command.args = (char **)ft_calloc(30, sizeof(char *)); // кол-во аргументов
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
					return (-1);
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
				char *quote_line; // кавычка
				quote_line = ft_strdup("");
				if (command.args[argc] == NULL)
					command.args[argc] = ft_strdup("");
				while (line[k] != '\"')
				{
					if (line[k] == '$') // идёт до след $
					{
						while (line[k] == '$')
							command.args[argc] = ft_strjoin_free(command.args[argc], parse_if_dollar(line, &k, &vars->list_env), 0);
					}
					else if (line[k] == '\\' && (line[k + 1] == '$' || line[k + 1] == '\\' || line[k + 1] == '\"'))
					{
						k++;
						quote_line = ft_strjoin_free(quote_line, char_convert_to_str(line[k]), 3);
						k++;
					}
					else
					{
						quote_line = ft_strjoin_free(quote_line, char_convert_to_str(line[k]), 3);
						k++;
					}
				}
				k++;
				command.args[argc] = ft_strjoin_free(command.args[argc], quote_line, 1);
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
					command.args[argc] = NULL; // and free()!!!!!!!!!!!
			}
			else if (line[k] == '#') // комментарий, это опционально
			{
				line[k] = '\0';
				break ;
			}
			else // это обычный аргумент, без каких-то спец символов
			{
				char *start;
				start = line + k;
				while (line[k] != ' ' && line[k] != ';' && line[k] != '\\'  && line[k] != '\'' && line[k] != '\"' && line[k] != '$' && line[k] != '\0')
					k++;
				if (command.args[argc] == NULL)
					command.args[argc] = ft_substr(start, 0, line + k - start);
				else
					command.args[argc] = ft_strjoin_free(command.args[argc], ft_substr(start, 0, line + k - start), 3);
			}
			if (line[k] == ';' || line[k] == '\0')
				break ;
			if (line[k] == ' ')
				argc++;
			while (line[k] == ' ')
				k++;
		}
		signal (SIGQUIT, SIG_DFL);
		signal (SIGINT, SIG_DFL);
		if (vars->f_pipe == TRUE) //			!!!
			make_pipe(&command, vars); //		!!!
		else //									!!!
			processing(&command, vars); //		!!!
		signal (SIGQUIT, SIG_IGN);
		signal (SIGINT, SIG_IGN);
		dup2(STDIN_FILENO, 0); //  				!!!
		dup2(STDOUT_FILENO, 1); // 				!!!
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
// echo "This $"
// echo " ' " " ' "
// export $qwe=123; echo "This \$qwe"\=$qwe\ \!
// export qwe=$; echo "This \$qwe"$qwePATH

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