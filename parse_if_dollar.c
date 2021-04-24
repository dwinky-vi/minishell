/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_if_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 19:44:14 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/24 21:31:54 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_minishell.h"

char	*get_value_in_lst_for_parser(t_list *list_env, char *key)
{
	while (list_env)
	{
		if (ft_strncmp(((t_envp *)list_env->content)->name, key, ft_strlen(key) + 1) == 0)
		{
			return (ft_strdup(((t_envp *)list_env->content)->value));
		}
		list_env = list_env->next;
	}
	return (ft_strdup(""));
}
		/** need to free tree result */
char	*parse_if_dollar(char *line, size_t *k, t_list **head_lst)
{
	size_t	size;
	char	*key;
	char	*value;
	t_list	*list_env;

	(*k)++;
	list_env = *head_lst;
	size = 0;
	if (ft_isdigit(line[*k]))
	{
		*k += 1;
		return (ft_strdup(""));
	}
	else if (line[*k] == '$')
	{
		*k += 1;
		return (ft_strdup(""));
	}
	else if (line[*k] == '?')
	{
		*k += 1;
		// vars.code
		return (ft_strdup(""));
	}
	else if (line[*k] == '\0' || line[*k] == ' ' || line[*k] == ';' || line[*k] == '\'' || line[*k] == '\"' || line[*k] == '\\')
	{
		return (ft_strdup("$"));
	}
	while (ft_isalnum(line[*k + size]) && line[*k + size] != '\0')
		size++;
	key = ft_substr(line + *k, 0, size);
	value = get_value_in_lst_for_parser(list_env, key);
	*k += size;
	free(key);
	return (value);
}
