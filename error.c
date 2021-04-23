/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:51:39 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/23 18:51:42 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

int	syntax_error(char *token)
{
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd("syntax error near unexpected token `", 1);
	ft_putstr_fd(token, 1);
	ft_putstr_fd("'\n", 1);
	return (TRUE);
}
