/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 03:30:04 by aquinoa           #+#    #+#             */
/*   Updated: 2021/03/31 21:45:00 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base(unsigned int nb, int base)
{
	if (nb >= 10)
	{
		if (base < 10)
			ft_putnbr_base(nb / 10, base);
		else
		{
			ft_putchar_fd(nb + 55, 1);
			return (0);
		}
	}
	ft_putchar_fd(nb + 48, 1);
	return (0);
}

void	ft_itoa_base(unsigned int nb, int base)
{
	if (nb > (unsigned int)base)
		ft_itoa_base(nb / base, base);
	ft_putnbr_base(nb % base, base);
}
