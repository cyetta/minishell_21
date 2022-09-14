/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_qsp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:27:25 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/14 23:11:48 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <stdlib.h>
//#include "minishell.h"
#include "lexer.h"
#include "ft_error.h"

/*
adds token 'space'  in list
return ERR_MALLOC if memory allocation error
tkn_lst - token list
str - string for parsing
pos - position, that point to current char in parsing string
*/
int	add_tkn_sp(t_list **tkn_lst, char *str, int *pos)
{
	t_list	*tkn;

	if (new_tkn_elmnt(&tkn, SPACESTR, NULL))
		return (ERR_MALLOC);
	while (ft_isspace(str[*pos + 1]))
		(*pos)++;
	ft_lstadd_back(tkn_lst, tkn);
	return (ERR_OK);
}

/*
adds token 'quotes'  in list
return ERR_MALLOC if memory allocation error
tkn_lst - token list
str - string for parsing
pos - position, that point to current char in parsing string
*/
int	add_tkn_quotes(t_list **tkn_lst, char *str, int *pos)
{
	t_list	*tkn;
	char	*nextq;
	int		subslen;

	if (new_tkn_elmnt(&tkn, QUOTES, NULL))
		return (ERR_MALLOC);
	(*pos)++;
	nextq = ft_strchr(&str[*pos], '\'');
	if (!nextq)
		return (ERR_SYNTAX_OPNQUOTES);
	subslen = nextq - &str[*pos];
	((t_token *)tkn->content)->value = ft_substr(str, *pos, subslen);
	*pos += subslen;
	if (!((t_token *)tkn->content)->value)
		return (ERR_MALLOC);
	ft_lstadd_back(tkn_lst, tkn);
	return (ERR_OK);
}

/*
adds token 'double quotes'  in list
return ERR_MALLOC if memory allocation error
tkn_lst - token list
str - string for parsing
pos - position, that point to current char in parsing string
*/
int	add_tkn_dquotes(t_list **tkn_lst, char *str, int *pos)
{
	t_list	*tkn;
	char	*nextq;
	int		subslen;

	if (new_tkn_elmnt(&tkn, DQUOTES, NULL))
		return (ERR_MALLOC);
	(*pos)++;
	nextq = ft_strchr(&str[*pos], '\"');
	if (!nextq)
		return (ERR_SYNTAX_OPNQUOTES);
	subslen = nextq - &str[*pos];
	((t_token *)tkn->content)->value = ft_substr(str, *pos, subslen);
	*pos += subslen;
	if (!((t_token *)tkn->content)->value)
		return (ERR_MALLOC);
	ft_lstadd_back(tkn_lst, tkn);
	return (ERR_OK);
}

/*
adds token 'string'  in list
return ERR_MALLOC if memory allocation error
tkn_lst - token list
str - string for parsing
pos - position, that point to current char in parsing string
*/
int	add_tkn_str(t_list **tkn_lst, char *str, int *pos)
{
	t_list	*tkn;

	if (new_tkn_elmnt(&tkn, STRINGLN, NULL))
		return (ERR_MALLOC);
	((t_token *)tkn->content)->value = get_subs(str, pos);
	if (!((t_token *)tkn->content)->value)
		return (ERR_MALLOC);
	(*pos)--;
	ft_lstadd_back(tkn_lst, tkn);
	return (ERR_OK);
}
