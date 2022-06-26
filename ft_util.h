/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 18:56:52 by cyetta            #+#    #+#             */
/*   Updated: 2022/06/26 21:26:35 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTIL_H
# define FT_UTIL_H
# include "ft_lib/libft.h"

int		ft_strcmp(const char *s1, const char *s2);
void	*ft_lstsearch(t_list *lst, void *key, int (*cmp)(void *, void *));
void	ft_lstdelnode(t_list **root, t_list *node, void (*del_cntnt)(void *));
void	ft_lstinsbeforenode(t_list **root, t_list *node, t_list *new);
void	ft_lstinsafternode(t_list **root, t_list *node, t_list *new);
#endif
