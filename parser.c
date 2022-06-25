/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:09:13 by cyetta            #+#    #+#             */
/*   Updated: 2022/06/25 21:18:31 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "ft_error.h"

int	tknlst_expander(t_mshell *data)
{
	t_list	*tknlst_hd;
	t_token	*tkn;
	char	*str;

	tknlst_hd = data->tkn_lst;
	while (tknlst_hd)
	{
		tkn = ((t_token *)tknlst_hd->content);
		if (tkn->e_lxm == DQUOTES)
		{
			str = expnd_str(tkn->value, data);
			free (tkn->value);
			tkn->e_lxm = STRINGLN;
			tkn->value = str;
		}
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
