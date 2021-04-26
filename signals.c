/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 19:54:54 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/26 12:40:27 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	signal_on(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	signal_off(void)
{
	signal (SIGINT, SIG_IGN);  //  ctrl-C.  Код сигнала –– 2
	signal (SIGQUIT, SIG_IGN);  // ctrl-\. Код сигнала –– 3
	// signal (SIGTERM, SIG_IGN); // !!! Игнорирует сигнал прерывания процесса  (ЗАЩИТА ОТ kill minishell) !!!
}
