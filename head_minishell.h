/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head_minishell.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 17:55:01 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/07 23:44:11 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_MINISHELL_H
# define HEAD_MINISHELL_H

# include "./libft/libft.h"
# include <stdio.h>
# include <errno.h>
# include <term.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>

# define TRUE 1
# define FALSE 0
# define BUFSIZE 1024

typedef struct s_envp
{
	char	*name;
	char	*value;
}				t_envp;

typedef struct s_command
{
	char	*name;
	char	**args;
	int		fd[2];
}				t_command;

void			processing(t_command *cmd, t_list **list_env, char **envp);
char			*get_env(t_list **list_env, char *key);
int				make_cd(t_command *cmd, t_list **list_env);
void			make_echo(t_command *cmd);
void			make_pwd(t_command *cmd);
void			make_env(t_command *cmd, t_list **list_env);
void			make_other(t_command *cmd, t_list **list_env, char **envp);

#endif
