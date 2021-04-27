#include "head_minishell.h"

void	clear_command_line(int cursor_pos, char *previous_history)
{
	int	len;

	if (previous_history == NULL)
		len = 0;
	else
		len = ft_strlen(previous_history);
	while (cursor_pos < len)
	{
		tputs(cursor_right, 1, ft_putchar);
		cursor_pos++;
	}
	while (cursor_pos > 0)
	{
		tputs(cursor_left, 1, ft_putchar);
		tputs(delete_character, 1, ft_putchar);
		cursor_pos--;
	}
}
