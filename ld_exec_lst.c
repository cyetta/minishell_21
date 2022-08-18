/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_exec_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 23:42:46 by cyetta            #+#    #+#             */
/*   Updated: 2022/08/18 14:38:42 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "ft_error.h"

/*
converts struct t_ktabe to allocated string
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
clean enviroment variable array
*/
void	a_env_free(t_mshell *data)
{
	int	i;

	if (data->a_env)
	{
		i = 0;
		while (data->a_env[i])
			free(data->a_env[i++]);
		free(data->a_env);
		data->a_env = NULL;
	}
}

/*
load enviroment variable array for command with actual value from list
*/
int	a_env_init(t_mshell *data)
{
	int		qnt;
	int		j;
	t_list	*i;

	a_env_free(data);
	qnt = ft_lstsize(data->env_lst);
	data->a_env = malloc(sizeof(char *) * (++qnt));
	if (!data->a_env)
		exit(ft_error(ERR_MALLOC));
	j = 0;
	i = data->env_lst;
	while (i)
	{
		data->a_env[j++] = ktable2str((t_ktable *)i->content);
		i = i->next;
	}
	data->a_env[j] = NULL;
	return (ERR_OK);
}

int	ld_exec_lst(t_mshell *data)
{
	data->exec_lst = NULL;
	a_env_init(data);
	return (ERR_OK);
}
/* 	int	i = -1;
	while ((data->a_env)[++i])
		printf("a_env: %s\n", data->a_env[i]);
 */