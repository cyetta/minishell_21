/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 11:04:22 by cyetta            #+#    #+#             */
/*   Updated: 2022/06/21 15:12:27 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"
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

	if (new_tkn_elmnt(&tkn))
		return (ERR_MALLOC);
	((t_token *)tkn->content)->e_lxm = SPACESTR;
	while (ft_isspace(str[*pos + 1]))
		(*pos)++;
	ft_lstadd_back(tkn_lst, tkn);
	return (ERR_OK);
}

/*
Creates new list element with token
if memory allocation error return ERR_MALLOC(6)
*/
int	new_tkn_elmnt(t_list **new_tkn)
{
	t_token	*tkn;

	tkn = malloc(sizeof(t_token));
	if (!tkn)
		return (ERR_MALLOC);
	tkn->value = NULL;
	tkn->e_lxm = SPACESTR;
	*new_tkn = ft_lstnew(tkn);
	if (*new_tkn)
		return (ERR_OK);
	free(tkn);
	return (ERR_MALLOC);
}

/*
Print token
callback function for ft_lstiter()
*/
void	prn_tkn_elmnt(void *elm)
{
	t_token	*itm;
	static char	*tkn[] = {"SPACESTR", "QUOTES", "DQUOTES", "DOLLAR", "PIPE", \
	"REDIR_IN", "REDIR_OUT", "DREDIR_OUT", "HERE_DOC", "STRINGLN"};

	if (!elm)
		return ;
	itm = (t_token *)elm;
	printf("%s : %s\n", tkn[itm->e_lxm], itm ->value);
}

/*
Frees tokens content and itself
Callback function for ft_lstclear()
*/
void	del_tkn_elmnt(void *elm)
{
	t_token	*tkn;

	tkn = (t_token *)elm;
	if (tkn->value)
		free(tkn->value);
	free(tkn);
}

static int	add_tkn(t_list **tkn_lst, char *str, int *pos)
{
	int	err;

	if (ft_isspace(str[*pos]))
		err = add_tkn_sp(tkn_lst, str, pos);
	else if (str[*pos] == '\'')
		err = add_tkn_quotes(tkn_lst, str, pos);
	else if (str[*pos] == '\"')
		err = add_tkn_dquotes(tkn_lst, str, pos);
	else if (str[*pos] == '$')
		err = add_tkn_dollar(tkn_lst, str, pos);
	else if (str[*pos] == '|')
		err = add_tkn_pipe(tkn_lst, str, pos);
	else if (str[*pos] == '<')
		err = add_tkn_rdrin(tkn_lst, str, pos);
	else if (str[*pos] == '>')
		err = add_tkn_rdrout(tkn_lst, str, pos);
	else
		err = add_tkn_str(tkn_lst, str, pos);
	return (err);
}

int	lexer(t_list **tkn_lst, char *str)
{
	int	i;
	int	err;

	i = -1;
	while (str[++i])
	{
		err = add_tkn(tkn_lst, str, &i);
		if (err)
		{
			ft_lstclear(tkn_lst, del_tkn_elmnt);
			return (err);
		}
	}
	return (0);
}
