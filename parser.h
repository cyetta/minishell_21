/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:09:06 by cyetta            #+#    #+#             */
/*   Updated: 2022/08/08 21:05:14 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"
# include "ft_util.h"

int		tknlst_expander(t_mshell *data);
char	*get_envvalue(char *str, t_list *env);
char	*get_envvar(char *str, t_mshell *data, int *pos);
char	*expnd_str(char *str, t_mshell *data);
int		f_tkn_space(t_list **tknlst_hd, t_mshell *data);
int		f_tkn_pipe(t_list **tknlst_hd, t_mshell *data);
int		f_tkn_quotes(t_list **tknlst_hd, t_mshell *data);
int		f_tkn_dquotes(t_list **tknlst_hd, t_mshell *data);
int		f_tkn_str(t_list **tknlst_hd, t_mshell *data);
int		f_tkn_dollar(t_list **tknlst_hd, t_mshell *data);
#endif
