/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tkn2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:09:13 by cyetta            #+#    #+#             */
/*   Updated: 2022/08/08 21:04:29 by cyetta           ###   ########.fr       */
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
