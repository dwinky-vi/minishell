/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:58:51 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/27 22:24:11 by dwinky           ###   ########.fr       */
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

	if (lexer(line) == FAILURE_CODE)
		return (FAILURE_CODE);
	line = ft_strdup(line);
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
				if (command.args[argc] == NULL)
					command.args[argc] = ft_strdup("");
				command.args[argc] = ft_strjoin_free(command.args[argc], parse_if_quote_one(line, &k), 3);
				k++;
			}
			else if (line[k] == '\"')
			{
				if (command.args[argc] == NULL)
					command.args[argc] = ft_strdup("");
				k++;
				while (line[k] != '\"')
				{
					if  (line[k] == '$')
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
			}
			else if (line[k] == '\\')
			{
				if (command.args[argc] == NULL)
					command.args[argc] = ft_strdup("");
				command.args[argc] = ft_strjoin_free(command.args[argc], char_convert_to_str(line[k + 1]), 3);
				k += 2;
			}
			else if (line[k] == '$')
			{
				if (command.args[argc] == NULL)
					command.args[argc] = ft_strdup("");
				while (line[k] == '$')
					command.args[argc] = ft_strjoin_free(command.args[argc], parse_if_dollar(line, &k, &vars->list_env), 3);
				if (command.args[argc][0] == '\0')
				{
					free(command.args[argc]);
					command.args[argc] = NULL;
				}
			}
			else if (line[k] == '|')
			{
				vars->f_pipe = TRUE;
				k++;
				break ;
			}
			else if (line[k] == '>')
			{
				if (vars->f_redir == TRUE)
					close(command.fd[1]);
				vars->f_redir = TRUE;
				char *file_name;
				file_name = ft_strdup("");
				if (line[k] == '>' && line[k + 1] == '>')
				{
					k += 2;
					while (line[k] == ' ')
						k++;
					int start = k;
					// while (line[k] != ' ' && line[k] != ';' && line[k] != '|' && line[k] != '>' && line[k] != '<' && line[k] != '\0')
					// {
					// 	if (line[k] = '\'')
					// 	{
							
					// 	}
					// 	else if (line[k] = '\"')
					// 	{
							
					// 	}
					// 	else if (line[k] = '\\')
					// 	{
							
					// 	}
					// 	else if (line[k] = '$')
					// 	{
					// 		while (line[k] == '$')
					// 			file_name = ft_strjoin_free(file_name, parse_if_dollar(line, &k, &vars->list_env), 3);
					// 	}
					// 	k++;
					// }
					file_name = ft_substr(line, start, k - start);
					command.fd[1] = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
					if (command.fd[1] == -1)
					{
						ft_putendl_fd(strerror(errno), 1);
						return (FAILURE_CODE);
					}
					free(file_name);
				}
				else if (line[k] == '>')
				{
					k++;
					while (line[k] == ' ')
						k++;
					int start = k;
					while (line[k] != ' ' && line[k] != ';' && line[k] != '|' && line[k] != '>' && line[k] != '<' && line[k] != '\0')
						k++;
					file_name = ft_substr(line, start, k - start);
					command.fd[1] = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
					if (command.fd[1] == -1)
					{
						ft_putendl_fd(strerror(errno), 1);
						return (FAILURE_CODE);
					}
					free(file_name);
				}
				dup2(command.fd[1], 1); //				!!! Заменяю fd для записи в файл !!!
				while (line[k] == ' ')
					k++;
			}
			else if (line[k] == '<')
			{
				if (parse_if_back_redir(vars, &command, line, &k) == FAILURE_CODE)
					return (FAILURE_CODE);
			}
			else // это обычный аргумент, без каких-то спец символов
			{
				char *start;
				start = line + k;
				while (line[k] != ' ' && line[k] != ';' && line[k] != '\\'  && line[k] != '\'' && line[k] != '\"' && line[k] != '$' && line[k] != '|' && line[k] != '>' && line[k] != '<' && line[k] != '\0')
					k++;
				if (command.args[argc] == NULL)
					command.args[argc] = ft_substr(start, 0, line + k - start);
				else
					command.args[argc] = ft_strjoin_free(command.args[argc], ft_substr(start, 0, line + k - start), 3);
			}
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
		vars->f_pipe = FALSE;
		vars->f_redir = FALSE;
		free_command(&command);
		if (line[k] == ';')
			k++;
	}
	free(command.args);
	free(line);
	return (SUCCESS_CODE);
}
