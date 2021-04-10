/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 17:07:29 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/10 19:02:29 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	ft_putline(char *s1, char *s2, char *s3)
{
	ft_putstr_fd(s1, 1);
	ft_putstr_fd(s2, 1);
	ft_putstr_fd(s3, 1);
}

void	ft_putline_nbr(char *s1, int nbr)
{
	ft_putstr_fd(s1, 1);
	ft_putnbr_fd(nbr, 1);
	ft_putstr_fd("\n", 1);
}

int	ft_putchar(int ch)
{
	write(1, &ch, 1);
	return (0);
}

void	print_prompt(void)
{
	write(1, "\e[1;35m", 7); // the color
	write(1, "bash-3.2$ ", 10);
	write(1, "\e[0m", 4);
}