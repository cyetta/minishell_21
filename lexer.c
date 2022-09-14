/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 11:04:22 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/14 23:14:09 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"
#include "lexer.h"
#include "ft_error.h"

/*
Creates new list element with token
if memory allocation error return ERR_MALLOC(6)
*/
int	new_tkn_elmnt(t_list **new_tkn, t_lexeme lxm, char *value)
{
	t_token	*tkn;

	tkn = malloc(sizeof(t_token));
	if (!tkn)
		return (ERR_MALLOC);
	tkn->e_lxm = lxm;
	tkn->value = value;
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
void	tkn_elmnt_prn(void *elm)
{
	t_token		*itm;
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
void	tkn_elmnt_del(void *elm)
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
			ft_lstclear(tkn_lst, tkn_elmnt_del);
			return (err);
		}
	}
	return (0);
}
