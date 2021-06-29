/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_if_back_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 21:18:02 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/29 21:55:36 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

int	redir_error(t_vars *vars, t_command *command, char *file_name)
{
	vars->f_redir_0 = FALSE;
	command->fd[0] = vars->tmp_fd_0;
	g_code = 1;
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(file_name, 1);
	ft_putstr_fd(": ", 1);
	ft_putendl_fd(strerror(errno), 1);
	free(file_name);
	return (FAILURE_CODE);
}

int	parse_if_back_redir(char *line, size_t *k, t_vars *vars, t_command *command)
{
	char	*file_name;

	if (vars->f_redir_0 == TRUE)
		close(command->fd[0]);
	vars->f_redir_0 = TRUE;
	(*k)++;
	if (line[*k] == '>')
		return (SUCCESS_CODE);
	while (line[*k] == ' ')
		(*k)++;
	get_file_name(line, k, vars, &file_name);
	command->fd[0] = open(file_name, O_RDWR, 0644);
	if (command->fd[0] == -1)
		return (redir_error(vars, command, file_name));
	dup2(command->fd[0], 0);
	free(file_name);
	while (line[*k] == ' ')
		(*k)++;
	return (SUCCESS_CODE);
}
