/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 17:14:41 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/14 03:04:33 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

char	*get_term_name(t_list *lst)
{
	while (lst)
	{
		if (ft_strncmp(((t_envp *)lst->content)->name, "TERM", 5) == 0)
			return (((t_envp *)lst->content)->value);
		lst = lst->next;
	}
	return ("xterm-256color"); // as default
}

int	init_term(struct termios *term, char *term_name)
{
	if (tcgetattr(0, term) == -1)
		exit (0);
	term->c_lflag &= ~(ECHO); // отключаем этот флаг (бит) устанавливается на ноль. Отключаем, чтобы read показывал, что печатается
	term->c_lflag &= ~(ICANON); //переводим терминал в НЕ каноническое. В каноническом виде read завершается по нажатию \n
	tcsetattr(0, TCSANOW, term);
	tgetent(0, term_name); // подгружаем базу данных нашего терминала
	return (0);
}

void	return_term(struct termios *term)
{
	term->c_lflag |= (ECHO); // ВОЗВРАТ НАСТРОЕК ТЕРМИНАЛА
	term->c_lflag |= (ICANON);
	tcsetattr(0, TCSANOW, term);
}
