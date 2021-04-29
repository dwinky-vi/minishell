/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 17:14:41 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/29 04:36:22 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

		/** "xterm-256color" –– as default */
char	*get_term_name(t_list *lst)
{
	while (lst)
	{
		if (ft_strncmp(((t_envp *)lst->content)->name, "TERM", 5) == 0)
			return (((t_envp *)lst->content)->value);
		lst = lst->next;
	}
	return ("xterm-256color");
}

void	init_term(struct termios *term, char *term_name)
{
	tcgetattr(0, term);
	term->c_lflag &= ~(ISIG);
	term->c_lflag &= ~(ECHO);
	term->c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, term);
	tgetent(0, term_name);
}

		/** возврат настроек терминала */
void	return_term(struct termios *term)
{
	term->c_lflag |= (ISIG);
	term->c_lflag |= (ECHO);
	term->c_lflag |= (ICANON);
	tcsetattr(0, TCSANOW, term);
}
