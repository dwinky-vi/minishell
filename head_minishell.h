/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head_minishell.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 17:55:01 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/21 19:39:24 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_MINISHELL_H
# define HEAD_MINISHELL_H

# include "./libft/libft.h"
# include <stdio.h> // printf
# include <errno.h> // strerror, errno
# include <term.h> // termcap function
# include <unistd.h> // write, read, fork, execve, getcwd, chdir, dup, dup2, pipe, pid_t
# include <stdlib.h> // malloc, free, exit
# include <string.h> // !!!!!!! strcmp !!!!!!!!!!
# include <signal.h> // signal, kill
# include <sys/stat.h> // stat, lstat, fstat
# include <sys/types.h> // fork, wait
# include <fcntl.h> // open
# include <sys/wait.h> // waitpid

// # include "head_parser.h"

# define TRUE 1
# define FALSE 0
# define BUFSIZE 1024

int			g_code;

typedef struct s_envp
{
	char	*name;
	char	*value;
}				t_envp;

typedef struct s_command
{
	struct termios	term;
	char	**args;
	int		fd[2];
}				t_command;

typedef struct s_vars
{
	char			**envp;
	t_list			*list_env;
	struct termios	term;
	int				miniflag;
	int				f_pipe;
	int				f_redir;
	char			*command;
	char			*history_path;
}				t_vars;

void			init_env(t_vars *vars);
void			processing(t_command *cmd, t_vars *vars);
char			*get_env_value(t_list *list_env, char *key);
void			make_cd(t_command *cmd, t_list *list_env);
void			make_echo(t_command *cmd, t_vars *vars);
void			make_pwd(t_command *cmd);
void			make_env(t_command *cmd, t_list *list_env);
void			make_other(t_command *cmd, t_list *list_env, char **envp);
void			make_unset(t_command *cmd, t_vars *vars);
void			make_export(t_command *cmd, t_vars *vars);
void			make_exit(t_command *cmd, t_vars *vars);
void 			mem_err();
char			**change_env(t_list *list_env, char *key);
void	add_list_env(char *str, t_list *list_env);
void	add_envp(t_vars *vars, char *str);
char	**envp_copy(char **envp);
void	new_envp(t_vars *vars);
void	delet_list(t_list **list_env);
void	env_err(t_command *cmd, int i);
void	make_pipe(t_command *cmd, t_vars *vars);

t_list	*get_env(char **envp);

char	*get_term_name(t_list *lst);

int		init_term(struct termios *term, char *term_name);

void	return_term(struct termios *term);

void	clear_command_line(int cursor_pos, char *previous_history);

int		get_history(char ***history, size_t *k, t_vars *vars);

void	set_history(char **history, int k, t_vars *vars);

int		ft_putchar(int ch);

void	print_prompt(void);

int		is_hotkey(char *str);

		/** keys **/
void	pressed_key_backspace(int *cursor_pos, char **line, char **history_line);

void	pressed_key_delete(int *cursor_pos, char **line, char **history_line);

void	pressed_key_home(int *cursor_pos, char **line);

void	pressed_key_end(int *cursor_pos, char **line);

		/** parser **/

int		parser(char *line, t_vars *vars);

void	ft_putline(char *s1, char *s2, char *s3);

void	ft_putline_nbr(char *s1, int nbr);

int		syntactic_parsing(char *line);

char	*parse_if_dollar(char *line, size_t *k, t_list **head_lst);

char	*parse_if_quote_one(char *line, size_t *k);

char	*get_value_in_lst_for_parser(t_list *list_env, char *key);

		/** lexer **/

int		lexer(char *line);
#endif
