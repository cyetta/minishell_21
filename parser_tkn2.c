/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tkn2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:09:13 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/26 15:37:50 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "ft_error.h"

int	f_tkn_dollar(t_list **tknlst_hd, t_mshell *data)
{
	int	i;

	i = -1;
	if ((*tknlst_hd)->next && ((t_token *)(*tknlst_hd)->next->content)->e_lxm \
	== STRINGLN)
		((t_token *)(*tknlst_hd)->content)->value = \
	get_envvar(((t_token *)(*tknlst_hd)->next->content)->value, data, &i);
	else
		((t_token *)(*tknlst_hd)->content)->value = ft_strdup("$");
	if (!((t_token *)(*tknlst_hd)->content)->value)
		return (ERR_MALLOC);
	if ((*tknlst_hd)->next && ((t_token *)(*tknlst_hd)->next->content)->e_lxm \
	== STRINGLN)
		ft_lstdelnode(tknlst_hd, (*tknlst_hd)->next, tkn_elmnt_del);
	((t_token *)(*tknlst_hd)->content)->e_lxm = STRINGLN;
	return (ERR_OK);
}
	// if(*((t_token *)(*tknlst_hd)->content)->value == '\0')
	// 	ft_lstdelnode(tknlst_hd, (*tknlst_hd)->next, del_tkn_elmnt);

int	f_tkn_redir(t_list **tknlst_hd, t_mshell *data)
{
	(void)data;
	if (!(*tknlst_hd)->next)
		return (ERR_SYNTAX_RDR);
	if (((t_token *)(*tknlst_hd)->next->content)->e_lxm == SPACESTR)
		ft_lstdelnode(tknlst_hd, (*tknlst_hd)->next, tkn_elmnt_del);
	if (!(*tknlst_hd)->next)
		return (ERR_SYNTAX_RDR);
	else if (((t_token *)(*tknlst_hd)->next->content)->e_lxm == PIPE)
		return (ERR_SYNTAX_PIPE);
	else if (((t_token *)(*tknlst_hd)->next->content)->e_lxm == REDIR_IN)
		return (ERR_SYNTAX_RDR_IN);
	else if (((t_token *)(*tknlst_hd)->next->content)->e_lxm == REDIR_OUT)
		return (ERR_SYNTAX_RDR_OUT);
	else if (((t_token *)(*tknlst_hd)->next->content)->e_lxm == DREDIR_OUT)
		return (ERR_SYNTAX_RDR_DOUT);
	else if (((t_token *)(*tknlst_hd)->next->content)->e_lxm == HERE_DOC)
		return (ERR_SYNTAX_RDR_HDOC);
	return (ERR_OK);
}

// collect string to from src to dest
int	token_collect(t_token *src, t_token *dest)
{
	char	*t;

	if (!src && !dest)
		return (err_prnt3n("minishell", "token_collect", "NULL pointer", \
	ERR_CTRLD_QUIT));
	if (dest)
		dest->e_lxm = STRINGLN;
	else
		return (err_prnt3n("minishell", "token_collect", "NULL destination pinter", \
		ERR_INIT_4));
	if (!src)
		return (ERR_OK);
	t = ft_strjoin(dest->value, src->value);
	if (!t)
		return (ERR_MALLOC);
	free (dest->value);
	dest->value = t;
	return (ERR_OK);
}

int	is_collected(t_token *t)
{
	return (t->e_lxm == QUOTES || t->e_lxm == DQUOTES \
	|| t->e_lxm == DOLLAR || t->e_lxm == STRINGLN);
}

int	f_tkn_hdoc(t_list **tknlst_hd, t_mshell *data)
{
	t_list	*tl;
	t_token	*t_tkn;
	int		err;

	err = f_tkn_redir(tknlst_hd, data);
	if (err)
		return (err);
	*tknlst_hd = (*tknlst_hd)->next;
	t_tkn = (t_token *)(*tknlst_hd)->content;
	tl = (*tknlst_hd)->next;
	err = 0;
	while (tl && !err && is_collected((t_token *)tl->content))
	{
		err = token_collect((t_token *)tl->content, t_tkn);
		ft_lstdelnode(tknlst_hd, tl, tkn_elmnt_del);
		tl = (*tknlst_hd)->next;
	}
	(*tknlst_hd) = tl;
	return (err);
}
