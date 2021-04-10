/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head_minishell.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:46:37 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/10 20:14:15 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_MINISHELL_H
# define HEAD_MINISHELL_H

# include "./libft/libft.h"
# include <stdio.h> // printf
# include <errno.h> // strerror, errno
# include <term.h> // termcap function
# include <unistd.h> // write, read, fork, execve, getcwd, chdir, dup, dup2, pipe
# include <stdlib.h> // malloc, free
# include <string.h> // !!!!!!! strcmp !!!!!!!!!!
# include <signal.h> // signal, kill
# include <sys/stat.h> // stat, lstat, fstat
# include <sys/types.h> // fork, wait
# include <fcntl.h> // open

# include "head_parser.h"

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

t_list	*get_env(char **envp);

char	*get_term_name(t_list *lst);

int		init_term(struct termios *term, char *term_name);

void	return_term(struct termios *term);

		/** keys **/
void	pressed_key_backspace(int *cursor_pos, char **line);

void	pressed_key_delete(int *cursor_pos, char **line);

void	pressed_key_home(int *cursor_pos, char **line);

void	pressed_key_end(int *cursor_pos, char **line);


char	**get_previous_history(int fd, size_t *k);
#endif
