/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_if_back_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 21:18:02 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/27 19:18:22 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

static int	redir_error(t_vars *vars, t_command *command, char *file_name)
{
	vars->f_redir = FALSE;
	command->fd[0] = vars->tmp_fd_0;
	g_code = 1;
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(file_name, 1);
	ft_putstr_fd(": ", 1);
	ft_putendl_fd(strerror(errno), 1);
	free(file_name);
	return (FAILURE_CODE);
}

int	parse_if_back_redir(t_vars *vars, t_command *command, char *line, size_t *k)
{
	char	*file_name;
	size_t	start;

	if (vars->f_redir == TRUE)
		close(command->fd[0]);
	vars->f_redir = TRUE;
	(*k)++;
	if (line[*k] == '>')
		return (SUCCESS_CODE);
	while (line[*k] == ' ')
		(*k)++;
	start = *k;
	while (is_special_character(line[*k]) == FALSE && line[*k] != '\0')
		(*k)++;
	file_name = ft_substr(line, start, *k - start);
	command->fd[0] = open(file_name, O_RDWR, 0644);
	if (command->fd[0] == -1)
		return (redir_error(vars, command, file_name));
	dup2(command->fd[0], 0);
	free(file_name);
	while (line[*k] == ' ')
		(*k)++;
	return (SUCCESS_CODE);
}