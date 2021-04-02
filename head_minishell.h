#ifndef HEAD_MINISHELL_H
# define HEAD_MINISHELL_H

# include "./libft/libft.h"
# include <stdio.h>
# include <errno.h>
# include <term.h>
# include <unistd.h>

typedef struct s_fd
{
	int		in;
	int		out;
}				t_fd;

typedef struct	s_comand
{
	char	*name;
	char	**args;
	t_fd	fd;
}				t_comand;

#endif
