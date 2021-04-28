#include "head_minishell.h"

void	parent_signal(int param)
{
	if (param == 2)
	{
		ft_putstr_fd("\n", 1);
		g_code = 130;
	}
	else if (param == 3)
	{
		ft_putendl_fd("Quit: 3", 1);
		g_code = 131;
	}
	else
		ft_putstr_fd("error\n", 1);
}

void	child_signal(int param)
{
	if (param == 2)
		g_code = 130;
	else if (param == 3)
		g_code = 131;
	else
		ft_putstr_fd("error\n", 1);
}
