/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head_parser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwinky <dwinky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:59:59 by dwinky            #+#    #+#             */
/*   Updated: 2021/04/12 22:59:27 by dwinky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_PARSER_H
# define HEAD_PARSER_H

# include "libft/libft.h"

int		parser(char *line, t_list *list_env, char **envp);

void	ft_putline(char *s1, char *s2, char *s3);

void	ft_putline_nbr(char *s1, int nbr);

int		syntactic_parsing(char *line);

#endif
