/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head_parser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:59:59 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/14 03:19:51 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_PARSER_H
# define HEAD_PARSER_H

# include "libft/libft.h"

typedef struct s_command
{
	struct termios	term;
	int		miniflag;
	char	**args;
	int		fd[2];
}				t_command;

int		parser(t_command *command, char *line, t_list *list_env, char **envp);

void	ft_putline(char *s1, char *s2, char *s3);

void	ft_putline_nbr(char *s1, int nbr);

int		ft_putchar(int ch);

void	print_prompt(void);

#endif
