/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tkn2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:09:13 by cyetta            #+#    #+#             */
/*   Updated: 2022/08/17 01:36:36 by cyetta           ###   ########.fr       */
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
		ft_lstdelnode(tknlst_hd, (*tknlst_hd)->next, del_tkn_elmnt);
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
		ft_lstdelnode(tknlst_hd, (*tknlst_hd)->next, del_tkn_elmnt);
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
