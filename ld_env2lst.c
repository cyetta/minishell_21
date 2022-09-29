/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_env2lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 20:53:28 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/29 14:49:51 by cyetta           ###   ########.fr       */
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
	printf("%s=%s\n", itm->key, itm ->value);
}

/*
converts struct t_ktabe to string(malloc)
key=value
if value == NULL return key
*/
char	*ktable2str(t_ktable *itm)
{
	char	*str;
	char	*tmp;

	str = ft_strdup(itm->key);
	if (!str)
		exit(ft_error(ERR_MALLOC));
	if (!itm->value)
		return (str);
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
		itm = parse_envstr(argp[i]);
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
