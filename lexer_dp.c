/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_dp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:39:59 by cyetta            #+#    #+#             */
/*   Updated: 2022/06/21 17:44:39 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <stdlib.h>
//#include "minishell.h"
#include "lexer.h"
#include "ft_error.h"

/*
adds token 'dollar'  in list
return ERR_MALLOC if memory allocation error
tkn_lst - token list
str - string for parsing
pos - position, that point to current char in parsing string
*/
int	add_tkn_dollar(t_list **tkn_lst, char *str, int *pos)
{
	t_list	*tkn;

	(void)str;
	(void)pos;
	if (new_tkn_elmnt(&tkn))
		return (ERR_MALLOC);
	((t_token *)tkn->content)->e_lxm = DOLLAR;
	ft_lstadd_back(tkn_lst, tkn);
	return (ERR_OK);
}

/*
adds token 'pipe' in list
return ERR_MALLOC if memory allocation error
tkn_lst - token list
str - string for parsing
pos - position, that point to current char in parsing string
*/
int	add_tkn_pipe(t_list **tkn_lst, char *str, int *pos)
{
	t_list	*tkn;

	(void)str;
	(void)pos;
	if (new_tkn_elmnt(&tkn))
		return (ERR_MALLOC);
	((t_token *)tkn->content)->e_lxm = PIPE;
	ft_lstadd_back(tkn_lst, tkn);
	return (ERR_OK);
}
