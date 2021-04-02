/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 00:40:23 by aquinoa           #+#    #+#             */
/*   Updated: 2020/11/12 16:01:10 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lst1;

	lst1 = *lst;
	if (lst1 == NULL)
		ft_lstadd_front(lst, new);
	while (lst1)
	{
		if (lst1->next == NULL)
		{
			lst1->next = new;
			new->next = NULL;
		}
		lst1 = lst1->next;
	}
}
