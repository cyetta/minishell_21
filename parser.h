/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:09:06 by cyetta            #+#    #+#             */
/*   Updated: 2022/06/26 19:03:20 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"
# include "ft_util.h"

int		tknlst_expander(t_mshell *data);
char	*get_envvalue(char *str, t_list *env);
char	*expnd_str(char *str, t_mshell *data);
#endif
