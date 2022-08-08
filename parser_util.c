/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 18:30:44 by cyetta            #+#    #+#             */
/*   Updated: 2022/08/08 20:40:22 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "ft_error.h"

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
