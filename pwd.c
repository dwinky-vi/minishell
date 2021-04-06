/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 01:32:19 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/06 14:24:23 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

# define BUFSIZE 1024

void	make_pwd(t_command *cmd)
{
	char	buf[BUFSIZE];

	getcwd(buf, BUFSIZE);
	ft_putendl_fd(buf, cmd->fd[1]);
}
