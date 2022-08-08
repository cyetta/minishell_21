/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_rdr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 18:44:28 by cyetta            #+#    #+#             */
/*   Updated: 2022/08/08 19:25:20 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <stdlib.h>
//#include "minishell.h"
#include "lexer.h"
#include "ft_error.h"

/*
adds token 'redirect in & here doc' in list
return ERR_MALLOC if memory allocation error
tkn_lst - token list
str - string for parsing
pos - position, that point to current char in parsing string
*/
int	add_tkn_rdrin(t_list **tkn_lst, char *str, int *pos)
{
	t_list	*tkn;

	if (new_tkn_elmnt(&tkn))
		return (ERR_MALLOC);
	((t_token *)tkn->content)->e_lxm = REDIR_IN;
	if (str[*pos + 1] == '<')
	{
		((t_token *)tkn->content)->e_lxm = HERE_DOC;
		(*pos)++;
	}
	ft_lstadd_back(tkn_lst, tkn);
	return (ERR_OK);
}

/*
adds token 'redirect out & double redirect out' in list
return ERR_MALLOC if memory allocation error
tkn_lst - token list
str - string for parsing
pos - position, that point to current char in parsing string
*/
int	add_tkn_rdrout(t_list **tkn_lst, char *str, int *pos)
{
	t_list	*tkn;

	if (new_tkn_elmnt(&tkn))
		return (ERR_MALLOC);
	((t_token *)tkn->content)->e_lxm = REDIR_OUT;
	if (str[*pos + 1] == '>')
	{
		((t_token *)tkn->content)->e_lxm = DREDIR_OUT;
		(*pos)++;
	}
	ft_lstadd_back(tkn_lst, tkn);
	return (ERR_OK);
}
