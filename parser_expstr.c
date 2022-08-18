/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 18:06:52 by cyetta            #+#    #+#             */
/*   Updated: 2022/08/18 13:12:48 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "minishell.h"

/*
return malloc() substring from position pos
to first symbol '$'
if malloc error return NULL
pos change to point to $
*/
char	*skip2dlr(char *str, int *pos)
{
	char	*subs;
	int		skip;

	subs = ft_strchr(&str[*pos], '$');
	if (subs)
		skip = subs - &str[*pos];
	else
		skip = ft_strlen(str) - *pos;
	subs = ft_substr(str, *pos, skip);
	(*pos) += skip;
	return (subs);
}

/*
Return last errolevel string
variable $?
*/
int	get_envquest(char *str, int *pos, char **subs, t_mshell *data)
{
	*subs = NULL;
	if (str[(*pos)] == '?')
		*subs = ft_itoa(data->errlvl);
	else if (str[(*pos)] == '0')
		*subs = ft_strdup("minishell");
	else
		return (0);
	(*pos)++;
	return (1);
}

/*
return malloc() substring with value of environment varialble, where variable
pointed by pos and begin from symbol '$'
if malloc error return NULL
pos change to point next substring after variable.
*/
char	*get_envvar(char *str, t_mshell *data, int *pos)
{
	char	*subs;
	char	*envq;
	char	*ret;

	++(*pos);
	if (get_envquest(str, pos, &envq, data))
	{
		subs = get_subs(str, pos);
		if (!subs)
			return (NULL);
		ret = ft_strjoin(envq, subs);
		free(envq);
		free(subs);
		return (ret);
	}
	subs = get_subs(str, pos);
	if (!subs)
		return (NULL);
	ret = get_envvalue(subs, data->env_lst);
	free(subs);
	return (ret);
}

static char	*expand_err(char *ret, char *tmp, char *subs)
{
	if (ret)
		free (ret);
	if (tmp)
		free (tmp);
	if (subs)
		free (subs);
	return (NULL);
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
char	*expnd_str(char *str, t_mshell *data)
{
	int		i;
	char	*ret;
	char	*tmp;
	char	*subs;

	if (!str || !str[0])
		return (ft_strdup(""));
	ret = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			subs = get_envvar(str, data, &i);
		else
			subs = skip2dlr(str, &i);
		if (!subs)
			return (expand_err(ret, tmp, subs));
		tmp = ret;
		ret = ft_strjoin(tmp, subs);
		if (!ret)
			return (expand_err(ret, tmp, subs));
		free(tmp);
		free(subs);
	}
	return (ret);
}
