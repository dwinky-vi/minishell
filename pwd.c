/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 01:32:19 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/28 11:18:23 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	make_pwd(t_command *cmd)
{
	char	buf[BUFSIZE];

	getcwd(buf, BUFSIZE);
	ft_putendl_fd(buf, 1);
}
