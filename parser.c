/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:09:13 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/01 20:57:07 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "ft_error.h"

typedef int	(*t_tkn_func)(t_list **, t_mshell *);

/*
Expands token via a_tkn_f and collect STRINGLN to one string
if sequence of token converts to sequence STRINGLN
*/
int	tkn_clct_str(t_list **tknlst_hd, t_mshell *data, const t_tkn_func *a_tkn_f)
{
	t_list		*t;
	int			err;
	char		*str;

	t = *tknlst_hd;
	err = a_tkn_f[((t_token *)t->content)->e_lxm](&t, data);
	while (t && t->next && !err && ((t_token *)t->content)->e_lxm == STRINGLN)
	{
		err = a_tkn_f[((t_token *)t->next->content)->e_lxm](&t->next, data);
		if (!t->next || ((t_token *)t->next->content)->e_lxm != STRINGLN)
			break ;
		str = ft_strjoin(((t_token *)t->content)->value, ((t_token *)t->next-> \
content)->value);
		if (!str)
			return (ERR_MALLOC);
		free(((t_token *)t->content)->value);
		((t_token *)t->content)->value = str;
		ft_lstdelnode(&t, t->next, tkn_elmnt_del);
	}
	if (t->next && ((t_token *)t->next->content)->e_lxm == SPACESTR)
		ft_lstdelnode(&t, t->next, tkn_elmnt_del);
	return (err);
}

/*
converts token list to string list, expand enviroment variable to string, check
some syntax
*/
int	tknlst_expander(t_mshell *data)
{
	t_list				*tknlst_hd;
	t_list				*prev;
	int					err;
	const t_tkn_func	a_tkn_f[] = {f_tkn_space, f_tkn_quotes, \
	f_tkn_dquotes, f_tkn_dollar, f_tkn_pipe, f_tkn_redir, f_tkn_redir, \
	f_tkn_redir, f_tkn_redir, f_tkn_str};

	tknlst_hd = data->tkn_lst;
	prev = NULL;
	while (tknlst_hd)
	{
		if (prev)
			err = tkn_clct_str(&(prev->next), data, a_tkn_f);
		else
			err = tkn_clct_str(&(data->tkn_lst), data, a_tkn_f);
		if (err)
			return (err);
		prev = tknlst_hd;
		tknlst_hd = tknlst_hd->next;
		if (((t_token *)prev->content)->e_lxm == STRINGLN && \
			*((t_token *)prev->content)->value == '\0')
			ft_lstdelnode(&data->tkn_lst, prev, tkn_elmnt_del);
	}
	return (ERR_OK);
}
