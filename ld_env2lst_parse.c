/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_env2lst_parse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 20:53:28 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/29 14:49:27 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"
#include "ft_error.h"

static t_ktable	*parse_envstr_u(t_ktable *envitm, char *str, char *pos_eq)
{
	if (!pos_eq)
		envitm->key = ft_strdup(str);
	else
		envitm->key = ft_substr(str, 0, pos_eq - str);
	if (!envitm->key)
	{
		free (envitm);
		return (NULL);
	}
	if (!pos_eq)
		envitm->value = NULL;
	else
	{
		envitm->value = ft_substr(str, (unsigned int)(pos_eq - str + 1), \
	strlen(pos_eq + 1));
		if (!envitm->value)
		{
			free(envitm->key);
			free(envitm);
			return (NULL);
		}
	}
	return (envitm);
}

/*
Create new element of environment list from string KEY=VALUE
return pointer to struct t_ktable (key, value)
*/
t_ktable	*parse_envstr(char *str)
{
	t_ktable		*envitm;
	char			*pos_eq;

	if (!str || (str && *str == '\0'))
		return (NULL);
	envitm = (t_ktable *)malloc(sizeof(t_ktable));
	if (!envitm)
		return (NULL);
	pos_eq = ft_strchr(str, '=');
	return (parse_envstr_u(envitm, str, pos_eq));
}
