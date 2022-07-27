/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:09:13 by cyetta            #+#    #+#             */
/*   Updated: 2022/06/30 22:19:19 by cyetta           ###   ########.fr       */
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
//	ft_lstdelnode(tknlst_hd, *tknlst_hd, del_tkn_elmnt);
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

int	f_tkn_dollar(t_list **tknlst_hd, t_mshell *data)
{
	if ((*tknlst_hd)->next && ((t_token *)(*tknlst_hd)->next->content)->e_lxm \
	== STRINGLN)
		((t_token *)(*tknlst_hd)->content)->value = get_envvalue(((t_token *) \
	(*tknlst_hd)->next->content)->value, data->env);
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

int	f_tkn_str(t_list **tknlst_hd, t_mshell *data)
{
	(void)data;
	(void)tknlst_hd;
	return (ERR_OK);
}
//	ft_lstdelnode(tknlst_hd, *tknlst_hd, del_tkn_elmnt);

typedef int	(*t_tkn_func)(t_list **, t_mshell *);

/*
Expands token via a_tkn_f and collect STRINGLN to one string
if sequence of token converts to sequence STRINGLN
*/
int	tkn_collect_str(t_list **tknlst_hd, t_mshell *data, const t_tkn_func *a_tkn_f)
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
		ft_lstdelnode(&t, t->next, del_tkn_elmnt);
	}
	if (t->next && ((t_token *)t->next->content)->e_lxm == SPACESTR)
		ft_lstdelnode(&t, t->next, del_tkn_elmnt);
	return (err);
}

/*
converts token list to string list
*/
int	tknlst_expander(t_mshell *data)
{
	t_list				*tknlst_hd;
	t_list				*prev;
	int					err;
	const t_tkn_func	a_tkn_f[] = {f_tkn_space, f_tkn_quotes, \
	f_tkn_dquotes, f_tkn_dollar, f_tkn_space, f_tkn_space, f_tkn_space, \
	f_tkn_space, f_tkn_str, f_tkn_str};

	tknlst_hd = data->tkn_lst;
	prev = NULL;
	while (tknlst_hd)
	{
		if (prev)
			err = tkn_collect_str(&(prev->next), data, a_tkn_f);
		else
			err = tkn_collect_str(&(data->tkn_lst), data, a_tkn_f);
		if (err)
			return (err);
		prev = tknlst_hd;
		tknlst_hd = tknlst_hd->next;
	}
	return (ERR_OK);
}

/*
compare ktable->key struct with key and
return true if its equal
*/
int	env_cmp(void *key, void *ktbl)
{
	char		*keystr;
	t_ktable	*srch;

	keystr = (char *)key;
	srch = (t_ktable *)ktbl;
	if (!ft_strcmp(keystr, srch->key))
		return (1);
	return (0);
}

/*
creates and returns a string in which the environment variable is expanded to
its value
str - environment variable string, env - list of environment variable
return
NULL - if malloc error
"\0" - if no value
"value\0" - sz of value
*/
char	*get_envvalue(char *str, t_list *env)
{
	t_ktable	*env_v;
	char		*subs;

	env_v = (t_ktable *)ft_lstsearch(env, str, env_cmp);
	if (env_v)
		subs = ft_strdup(env_v->value);
	else
		subs = ft_strdup("");
	return (subs);
}
