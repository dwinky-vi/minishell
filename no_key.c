/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_key.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 03:19:25 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/29 03:50:55 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

void	performing(char *line, int *cursor, t_vars *vars, t_history *history)
{
	ft_putstr_fd("\n", 1);
	parser(line, vars);
	print_prompt();
	*cursor = 0;
	if (history->current != history->size)
	{
		free(history->arr[history->current]);
		history->arr[history->current] = ft_strdup(history->old_arr[history->current]);
		history->current = history->size;
		// free(history->old_arr[history->current]);
		// history->old_arr[history->current]= NULL;
	}
	if (strcmp(line, ""))
	{
		free(history->arr[history->current]);
		history->arr[history->current] = ft_strdup(line);
		history->old_arr[history->current] = ft_strdup(line);
		history->size++;
		history->current = history->size;
	}
	ft_bzero(line, ft_strlen(line));
}

void	insert_inside(char *str, char **line, int *cursor, t_history *history)
{
	char *append;

	tputs(save_cursor, 1, ft_putchar);
	append = ft_strdup(*line + *cursor);
	(*line)[*cursor] = '\0';
	*line = ft_strjoin_free(*line, str, 1);
	*line = ft_strjoin_free(*line, append, 3);
	free(history->arr[history->current]);
	history->arr[history->current] = ft_strdup(*line);
	clear_command_line(*cursor, *line);
	ft_putstr_fd(*line, 1);
	tputs(restore_cursor, 1, ft_putchar);
	tputs(cursor_right, 1, ft_putchar);
	(*cursor)++;
}

void	write_characters(char *str, char **line, int *cursor, t_history *history)
{
	ft_putstr_fd(str, 1);
	*cursor += ft_strlen(str);
	*line = ft_strjoin_free(*line, str, 1);
	free(history->arr[history->current]);
	history->arr[history->current] = ft_strdup(*line);
}
