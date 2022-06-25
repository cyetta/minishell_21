/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:09:06 by cyetta            #+#    #+#             */
/*   Updated: 2022/06/25 20:48:37 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "ft_lib/libft.h"
# include "minishell.h"

int		tknlst_expander(t_mshell *data);
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_lstsearch(t_list *lst, void *key, int (*cmp)(void *, void *));
char	*get_envvalue(char *str, t_list *env);
char	*expnd_str(char *str, t_mshell *data);
#endif
