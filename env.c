/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 21:10:51 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/28 17:38:06 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	make_env(t_list *list_env)
{
	char	*str;
	t_list	*tmp_list;

	tmp_list = list_env;
	while (tmp_list)
	{
		str = ft_strjoin(((t_envp *)tmp_list->content)->name, "=");
		if (!str)
			mem_err();
		str = ft_strjoin_free(str, ((t_envp *)tmp_list->content)->value, 1);
		if (!str)
			mem_err();
		ft_putendl_fd(str, 1);
		free(str);
		tmp_list = tmp_list->next;
	}
}
