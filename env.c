/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 21:10:51 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/08 01:57:24 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	make_env(t_command *cmd, t_list **list_env)
{
	char	*str;
	t_list	*tmp_list;

	tmp_list = *list_env;
	while (tmp_list)
	{
		str = ft_strjoin(((t_envp *)tmp_list->content)->name, "=");
		str = ft_strjoin_free(str, ((t_envp *)tmp_list->content)->value, 1);
		ft_putendl_fd(str, 1);
		tmp_list = tmp_list->next;
	}
}
