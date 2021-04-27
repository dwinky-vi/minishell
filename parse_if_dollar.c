/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_if_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 19:44:14 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/27 22:23:51 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

char	*check_second_character(char *line, size_t *k)
{
	if (ft_isdigit(line[*k]))
	{
		*k += 1;
		return (ft_strdup(""));
	}
	else if (line[*k] == '$')
	{
		*k += 1;
		return (ft_strdup("$$"));
	}
	else if (line[*k] == '?')
	{
		*k += 1;
		return (ft_itoa(g_code));
	}
	else if (line[*k] == '\0' || line[*k] == ' ' || line[*k] == ';' || line[*k] == '\'' || line[*k] == '\"' || line[*k] == '\\')
		return (ft_strdup("$"));
	else if (line[*k] == '\'' || line[*k] == '\"')
		return (ft_strdup(""));
	return (NULL);
}

char	*get_env_parser(t_list *lst, char *key)
{
	int	tmp;

	while (lst)
	{
		tmp = ft_strncmp(((t_envp *)lst->content)->name, \
													key, \
													ft_strlen(key) + 1);
		if (tmp == 0)
			return (ft_strdup(((t_envp *)lst->content)->value));
		lst = lst->next;
	}
	return (ft_strdup(""));
}

		/** need to free the result */
char	*parse_if_dollar(char *line, size_t *k, t_list **head_lst)
{
	size_t	len;
	char	*key;
	char	*value;
	t_list	*list_env;

	list_env = *head_lst;
	len = 0;
	(*k)++;
	value = check_second_character(line, k);
	if (value != NULL)
		return (value);
	while (ft_isalnum(line[*k + len]) && line[*k + len] != '\0')
		len++;
	key = ft_substr(line + *k, 0, len);
	value = get_env_parser(list_env, key);
	*k += len;
	free(key);
	return (value);
}
