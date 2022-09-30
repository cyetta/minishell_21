/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tkn1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:09:13 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/30 20:38:32 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "ft_error.h"

int	f_tkn_space(t_list **tknlst_hd, t_mshell *data)
{
	(void)data;
	(void)tknlst_hd;
	return (ERR_OK);
}

int	f_tkn_pipe(t_list **tknlst_hd, t_mshell *data)
{
	if (!(*tknlst_hd)->next)
		return (ERR_SYNTAX_PIPE);
	else if (((t_token *)(*tknlst_hd)->next->content)->e_lxm == PIPE)
		return (ERR_SYNTAX_PIPE);
	else if (*tknlst_hd == data->tkn_lst)
		return (ERR_SYNTAX_PIPE);
	else if (((t_token *)(*tknlst_hd)->next->content)->e_lxm == SPACESTR)
		ft_lstdelnode(tknlst_hd, (*tknlst_hd)->next, tkn_elmnt_del);
	if (!(*tknlst_hd)->next)
		return (ERR_SYNTAX_PIPE);
	return (ERR_OK);
}

int	f_tkn_quotes(t_list **tknlst_hd, t_mshell *data)
{
	(void)data;
	((t_token *)(*tknlst_hd)->content)->e_lxm = STRINGLN;
	return (ERR_OK);
}

/*
function parse and update dquotes lexem in the list *tknlst_hd
*tknlst_hd point to the lexem. replaces string in dquotes with string
with opened evironment variable
returns ERR_OK if ok or ERR_MALLOC
*/
int	f_tkn_dquotes(t_list **tknlst_hd, t_mshell *data)
{
	t_token		*tkn;
	char		*str;

	tkn = ((t_token *)(*tknlst_hd)->content);
	str = expnd_str(tkn->value, data);
	if (!str)
		return (ERR_MALLOC);
	free (tkn->value);
	tkn->e_lxm = STRINGLN;
	tkn->value = str;
	return (ERR_OK);
}

int	f_tkn_str(t_list **tknlst_hd, t_mshell *data)
{
	(void)data;
	(void)tknlst_hd;
	return (ERR_OK);
}
