/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_previous_history.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 19:33:56 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/15 14:35:43 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

// возвращается индекс, начиная с которого идёт новая история
int		get_previous_history(char ***history, int fd, size_t *k)
{
    int r;
    char **history_buf;
    char *line;

    history_buf = *history;
    if (fd == -1)
        exit(1); // FIX IT
    history_buf = (char **) ft_calloc(500, sizeof(char *));
    if (history_buf == NULL)
        exit(1); // FIX IT
    while ((r = get_next_line(fd, &line)) >= 0) {
        if (*line != '\0')
            history_buf[(*k)++] = line;
        if (r == 0)
            break;
    }
    free(line);
    *history = history_buf;
    return (*k);
}
