/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:09:06 by cyetta            #+#    #+#             */
/*   Updated: 2022/06/22 19:32:55 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "ft_lib/libft.h"

int		ft_strcmp(const char *s1, const char *s2);
void	*ft_lstsearch(t_list *lst, void *key, int (*cmp)(void *, void *));

#endif
