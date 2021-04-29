/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head_minishell.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 17:55:01 by aquinoa           #+#    #+#             */
/*   Updated: 2021/04/29 03:57:14 by aquinoa          ###   ########.fr       */
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
# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

# ifndef BUFSIZE
#  define BUFSIZE 1024
# endif

# ifndef SUCCESS_CODE
#  define SUCCESS_CODE 0
# endif

# ifndef FAILURE_CODE
#  define FAILURE_CODE 1
# endif

# ifndef WIDTH_PROMT
#  define WIDTH_PROMT 12
# endif

int			g_code;

typedef struct s_envp
{
	char	*name;
	char	*value;
}				t_envp;

typedef struct s_command
{
	struct termios	term;
	char			**args;
	int				fd[2];
}				t_command;

typedef struct s_vars
{
	char			**envp;
	t_list			*list_env;
	struct termios	term;
	int				miniflag;
	int				f_pipe;
	int				f_redir_0;
	int				f_redir_1;
	char			*history_path;
	int				tmp_fd_0;
	int				tmp_fd_1;
	t_list			*export;
}				t_vars;

typedef struct s_history
{
	char	**arr;
	char	**old_arr;
	size_t	size;
	size_t	current;
	size_t	start_local_history;
}				t_history;

void			preprocessing(t_command *cmd, t_vars *vars);
void			processing(t_command *cmd, t_vars *vars);

void			make_echo(t_command *cmd);
void			make_cd(t_command *cmd, t_vars *vars);
void			make_pwd(void);
void			make_env(t_list *list_env);
void			make_export(t_command *cmd, t_vars *vars);
void			make_unset(t_command *cmd, t_vars *vars);
void			make_exit(t_command *cmd, t_vars *vars);
void			make_other(t_command *cmd, t_vars *vars);
void			make_pipe(t_command *cmd, t_vars *vars);

void			dot_err(int fd_1);
void			env_err(t_command *cmd, int i, int fd_1);
void			shell_err(char **args, int fd_1, int code, char *str);

void			init_env(t_vars *vars);
void			envp_copy(t_vars *vars, char **envp);
char			*get_env_value(t_list *list_env, char *key);
char			**change_env(t_list *list_env, char *key);
void			add_envp(t_vars *vars, char *str);
void			add_list_env(char *str, t_list *list_env);
void			new_envp(t_vars *vars);
char			**sort_env(t_list *list, int flag);

void			delet_list(t_list **list_env);
void			del_exp(t_list *exp);
int				check_key(t_command *cmd, char *key, int i, int fd_1);
void			check_exp(t_vars *vars, char *str);
void			adding_variable(char *str, t_vars *vars, char *key, char *val);
int				searching_variable(t_command *cmd, t_vars *vars, int i);
int				equal_sign(char *str);

void			parent_signal(int param);
void			child_signal(int param);

void			free_command(t_command *cmd);

// t_list	*get_env(char **envp);

char	*get_term_name(t_list *lst);

void	get_env_to_lst(t_vars *vars);

int		ft_find_in(char *str, char find);

void	ft_putline(char *s1, char *s2, char *s3);

void	ft_putline_nbr(char *s1, int nbr);
		/** terminal **/

void	init_term(struct termios *term, char *term_name);

void	return_term(struct termios *term);

int		ft_putchar(int ch);

void	print_prompt(void);

void	clear_command_line(int cursor_pos, char *previous_history);

int		is_hotkey(char *str);

void	signal_ctrl_c(char **line, int *cursor, t_history *history);

int		signal_ctrl_d(char **line, int *cursor, t_history *history);

void	pressed_key_up(char **line, int *cursor, t_history *history, char **old_history_line);

void	pressed_key_down(char **line, int *cursor, t_history *history, char **old_history_line);

		/** history **/

void	get_history(t_history *history, t_vars *vars);

void	set_history(t_history *history, t_vars *vars);

		/** keys **/

void	key_left_or_right(int *cursor_pos, char *str, char *line);

void	key_backspace_or_delete(char *str, char **line, int *cursor_pos, char **history_line);

void	pressed_key_delete(char **line, int *cursor_pos, char **history_line);

void	key_home_or_end(char *str, char *line, int *cursor_pos);

void	move_word(char *str, char *line, int *cursor_pos);

void	move_word_left(char *line, int *cursor_pos);

void	move_word_right(char *line, int *cursor_pos);

		/** parser **/

int		is_special_character(char ch);

int		redir_error(t_vars *vars, t_command *command, char *file_name);

int		parser(char *line, t_vars *vars);

char	*parse_if_quote_one(char *line, size_t *k);

char	*parse_if_quote_two(char *line, size_t *k, t_list *list_env);

char	*parse_if_dollar(char *line, size_t *k, t_list **head_lst);

int		parse_if_redir(char *line, size_t *k, t_vars *vars, t_command *command);

int		parse_if_back_redir(t_vars *vars, t_command *command, char *line, size_t *k);

char	*get_env_parser(t_list *list_env, char *key);

		/** lexer **/

int		lexer(char *line);

int		lexing_begin_line(char *line, size_t k);

int		lexing_special_character(char *line, size_t *k);

int		lexer_shielding(char *line, size_t *k);

int		lexer_quote(char *line, size_t *k);

int		lexer_pipe_or_redir(char *line, size_t *k);

int		lexer_pipe(char *line, size_t *k);

int		lexer_right_redir(char *line, size_t *k);

int		lexer_left_redir(char *line, size_t *k);

int		lexer_semicolon(char *line, size_t *k);

int		syntax_error(char *token);

#endif
