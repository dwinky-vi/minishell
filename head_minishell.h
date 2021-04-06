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

typedef struct s_envp
{
	char	*name;
	char	*value;
}				t_envp;

typedef struct	s_command
{
	char	*name;
	char	**args;
	int		fd[2];
}				t_command;

void			processing(t_command *cmd, t_list *env, char **envp);
void			make_echo(t_command *cmd);
void			make_pwd(t_command *cmd);
void			make_cd(t_command *cmd);
void			make_other(t_command *cmd, t_list *envp, char **env);

#endif
