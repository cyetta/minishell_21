/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:09:13 by cyetta            #+#    #+#             */
/*   Updated: 2022/06/22 20:15:03 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"

int	expander(t_list **tkn_lst)
{
	t_list	*tknlst_hd;

	tknlst_hd = *tkn_lst;
	while (tknlst_hd)
	{
		tknlst_hd = tknlst_hd->next;
	}
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
	char		*str;

	env_v = (t_ktable *)ft_lstsearch(env, str, env_cmp);
	if (env_v)
		str = ft_strdup(env_v->value);
	else
		str = ft_strdup("");
	return (str);
}

/*
creates and returns a string in which the environment variable is expanded to
its value
str - pointer to environment variable string
env - list of environment variable
return
NULL - if malloc error
"\0" - if no value
"value" - sz of value
*/
char	*expnd_dllr(char *str, t_list *env)
{
}
