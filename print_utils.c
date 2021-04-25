/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 17:07:29 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/25 04:25:34 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

#define LIGHT_GREEN	"\e[1;32m"
#define YELLOW "\e[1;33m"
#define CYAN "\e[1;36m"
#define NO_COLOR "\e[0m"
#define LIGHT_RED "\e[1;31m"
#define LIGHT_BLUE "\e[1;34m"
#define LIGHT_CYAN "\e[1;36m"
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
	write(1, LIGHT_CYAN, 7);
	write(1, "minishell-> ", 12);
	write(1, NO_COLOR, 4);
}
