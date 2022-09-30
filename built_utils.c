/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:37:11 by macbook           #+#    #+#             */
/*   Updated: 2022/09/30 21:52:11 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "builtins.h"
#include "ft_util.h"
#include "parser.h"
#include "ft_error.h"

/*
returns the structure of the environment variable according to the found variable
or NULL if no variable is found.
*/
t_ktable	*search_env_var(t_list *envlst, char *var)
{
	t_list	*t;

	t = ft_lstsearch(envlst, (void *)var, env_cmp);
	if (!t)
		return (NULL);
	return (t->content);
}

/*
Adds a variable to the environment list without checking for existence 
in the list. If var is NULL adds nothing,
If value is NULL, adds var c value NULL
In case of a memory allocation error, crashes with an error
*/
int	add_env_var(t_list **envlst, char *var, char *value)
{
	t_ktable	*v_env;
	t_list		*tl;

	if (!var)
		return (ERR_OK);
	v_env = (t_ktable *)malloc(sizeof(t_ktable));
	if (!v_env)
		exit(ft_error(ERR_MALLOC));
	v_env->key = ft_strdup(var);
	if (!v_env->key)
		exit(ft_error(ERR_MALLOC));
	if (value)
		v_env->value = ft_strdup(value);
	else
		v_env->value = NULL;
	if (value && !v_env->value)
		exit(ft_error(ERR_MALLOC));
	tl = ft_lstnew(v_env);
	if (!tl)
		exit(ft_error(ERR_MALLOC));
	ft_lstadd_back(envlst, tl);
	return (ERR_OK);
}

/*
Replaces the value of the var environment variable with val
or creates a variable if it does not exist
crashes if malloc() does not allocate memory
*/
int	replace_env_var(t_list **envlst, char *var, char *value)
{
	t_ktable	*v_env;

	v_env = search_env_var(*envlst, var);
	if (!v_env)
		add_env_var(envlst, var, value);
	else
	{
		if (v_env->value)
			free(v_env->value);
		if (value)
			v_env->value = ft_strdup(value);
		else
			v_env->value = NULL;
		if (value && !v_env->value)
			exit(ft_error(ERR_MALLOC));
	}
	return (ERR_OK);
}

/*
deletes the variable in the environment variable list
*/
int	del_env_var(t_list **envlst, char *var)
{
	t_list	*tl;

	tl = ft_lstsearch(*envlst, (void *)var, env_cmp);
	if (!tl)
		return (ERR_USAGE);
	ft_lstdelnode(envlst, tl, ktblitm_del);
	return (ERR_OK);
}
