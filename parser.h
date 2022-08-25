/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:09:06 by cyetta            #+#    #+#             */
/*   Updated: 2022/08/25 20:30:30 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"
# include "ft_util.h"

int		tknlst_expander(t_mshell *data);
char	*get_envvalue(const char *str, t_list *env);
char	*get_envvar(char *str, t_mshell *data, int *pos);
char	*expnd_str(char *str, t_mshell *data);
int		f_tkn_space(t_list **tknlst_hd, t_mshell *data);
int		f_tkn_pipe(t_list **tknlst_hd, t_mshell *data);
int		f_tkn_quotes(t_list **tknlst_hd, t_mshell *data);
int		f_tkn_dquotes(t_list **tknlst_hd, t_mshell *data);
int		f_tkn_str(t_list **tknlst_hd, t_mshell *data);
int		f_tkn_dollar(t_list **tknlst_hd, t_mshell *data);
int		f_tkn_redir(t_list **tknlst_hd, t_mshell *data);
int		ld_exec_lst(t_mshell *data);
int		a_env_init(t_mshell *data);
void	a_env_free(t_mshell *data);
void	exc_elmt_prn(void *elm);
void	exc_elmt_del(void *elm);
int		open_rdr(t_list **t, t_prgexec *p, t_mshell *data);
int		f_rdrin(t_list **t, t_prgexec *p, t_mshell *data);
int		f_rdrout(t_list **t, t_prgexec *p, t_mshell *data);
int		f_rdr2out(t_list **t, t_prgexec *p, t_mshell *data);
int		f_rdrhdoc(t_list **t, t_prgexec *p, t_mshell *data);
int		unlink_hdoc(t_mshell *data);
char	*get_tmpfname(const char *tmpenv, t_mshell *data);
char	*append_tmpfname(char *src_path, t_mshell *data);

#endif
