#ifndef HEAD_MINISHELL_H
# define HEAD_MINISHELL_H

# include "./libft/libft.h"
# include <stdio.h>
# include <errno.h>
# include <term.h>
# include <unistd.h>


typedef struct	s_command
{
	char	*name;
	char	**args;
	char	**fd;
	
}				t_command;

#endif
