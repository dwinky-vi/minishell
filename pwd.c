/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 01:32:19 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/28 17:37:30 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	make_pwd(void)
{
	char	buf[BUFSIZE];

	getcwd(buf, BUFSIZE);
	ft_putendl_fd(buf, 1);
}
