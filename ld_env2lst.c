/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_env2lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 20:53:28 by cyetta            #+#    #+#             */
/*   Updated: 2022/08/25 16:37:11 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"
#include "ft_error.h"

/*
Free t_ktable structure
callback function for ft_lstclear()
*/
void	ktblitm_del(void *elm)
{
	t_ktable	*itm;

	if (!elm)
		return ;
	itm = (t_ktable *)elm;
	if (itm->key)
		free(itm->key);
	if (itm->value)
		free(itm->value);
	free(itm);
}

/*
Print t_ktable fields
callback function for ft_lstiter()
*/
void	ktblitm_prn(void *elm)
{
	t_ktable	*itm;

	itm = (t_ktable *)elm;
	printf("%s : %s\n", itm->key, itm ->value);
}

/*
Create new element of environment list
return pointer to struct t_ktable (key, value)
*/
t_ktable	*get_envitm(char *str)
{
	t_ktable		*envitm;
	unsigned int	pos_eq;

	envitm = (t_ktable *)malloc(sizeof(t_ktable));
	if (!envitm)
		return (envitm);
	pos_eq = ft_strchr(str, '=') - str;
	envitm->key = ft_substr(str, 0, pos_eq);
	if (!envitm->key)
	{
		free (envitm);
		return (NULL);
	}
	envitm->value = ft_substr(str, pos_eq + 1, ft_strlen(str) - pos_eq + 1);
	if (!envitm->value)
	{
		free(envitm->key);
		free(envitm);
		return (NULL);
	}
	return (envitm);
}

/*
converts struct t_ktabe to string(malloc)
key=value
*/
char	*ktable2str(t_ktable *itm)
{
	char	*str;
	char	*tmp;

	str = ft_strdup(itm->key);
	if (!str)
		exit(ft_error(ERR_MALLOC));
	tmp = ft_strjoin(str, "=");
	free(str);
	if (!tmp)
		exit(ft_error(ERR_MALLOC));
	str = ft_strjoin(tmp, itm->value);
	free(tmp);
	if (!str)
		exit(ft_error(ERR_MALLOC));
	return (str);
}

/*
loads environment variable array to list t_ktable(key, value)
*/
int	ld_env2lst(t_list **lst, char **argp)
{
	t_list		*t;
	t_ktable	*itm;
	int			i;

	i = -1;
	while (argp[++i])
	{
		itm = get_envitm(argp[i]);
		if (!itm)
			break ;
		t = ft_lstnew(itm);
		if (!t)
		{
			ktblitm_del(itm);
			break ;
		}
		ft_lstadd_back(lst, t);
	}
	if (!argp[i])
		return (ERR_OK);
	ft_lstclear(lst, ktblitm_del);
	return (ERR_INIT_4);
}
