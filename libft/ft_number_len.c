/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 08:49:53 by aquinoa           #+#    #+#             */
/*   Updated: 2021/03/31 21:51:09 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_number_len(unsigned long long int nb)
{
	int		count;

	if (nb <= 0)
		count = 1;
	else
		count = 0;
	while (nb != 0)
	{
		nb /= 10;
		count++;
	}
	return (count);
}
