/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:37:11 by macbook           #+#    #+#             */
/*   Updated: 2022/09/26 21:28:35 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "builtins.h"
#include "ft_util.h"
#include "parser.h"
#include "ft_error.h"

/*
возвращает структуру переменной окружения по найденной переменной или 
NULL если переменная не найдена.
*/
t_ktable	*search_env_var(t_list *envlst, char *var)
{
	return ((t_ktable *)(ft_lstsearch(envlst, (void *)var, env_cmp))->content);
}

int	add_env_var(t_list **envlst, char *var, char *value)
{
	t_ktable	*v_env;
	t_list		*tl;

	v_env = (t_ktable *)malloc(sizeof(t_ktable));
	if (!v_env)
		exit(ft_error(ERR_MALLOC));
	v_env->key = ft_strdup(var);
	v_env->value = ft_strdup(value);
	if (!v_env->key || !v_env->value)
		exit(ft_error(ERR_MALLOC));
	tl = ft_lstnew(v_env);
	if (!tl)
		exit(ft_error(ERR_MALLOC));
	ft_lstadd_back(envlst, tl);
	return (ERR_OK);
}

/*
Заменяет значение переменной окружения var на val
или создает переменную если такой нет
крашится если malloc не выделит память
*/
int	replace_env_var(t_list **envlst, char *var, char *value)
{
	t_ktable	*v_env;

	v_env = search_env_var(*envlst, var);
	if (!v_env)
		add_env_var(envlst, var, value);
	else
	{
		free(v_env->value);
		v_env->value = ft_strdup(value);
		if (!v_env->value)
			exit(ft_error(ERR_MALLOC));
	}
	return (ERR_OK);
}

/*
удаляет переменную в списке переменных оружения 
*/
int	del_env_var(t_list **envlst, char *var)
{
	t_list	*tl;

	tl = ft_lstsearch(*envlst, (void *)var, env_cmp);
	if (tl)
		ft_lstdelnode(envlst, tl, ktblitm_del);
	return (ERR_OK);
}

/*char	*get_env_var(t_prgexec *cmd, char *var)
{
	int		i;
	char	*tmp;

	i = -1;
	while (cmd->argv[++i])
	{
		tmp = ft_strjoinch(var, '=');
		if (ft_strstartswith(cmd->argv[i], tmp))
		{
			free(tmp);
			return (ft_strchr(cmd->argv[i], '=') + 1);
		}
		free(tmp);
	}
	return (NULL);
}

char	*ft_strjoinch(char const *s1, char c)
{
	char	*new_str;
	size_t	i;
	size_t	s1_len;

	if (!s1 || !c)
		return (NULL);
	s1_len = ft_strlen(s1);
	new_str = ft_strnew(s1_len + 1);
	if (!new_str)
		return (NULL);
	i = -1;
	while (++i < s1_len)
		*(new_str + i) = *(s1 + i);
	*(new_str + i) = c;
	return (new_str);
}

int	ft_strstartswith(char *s1, char *s2)
{
	int	i;

	i = -1;
	while (s2[++i])
		if (s1[i] != s2[i])
			return (0);
	return (1);
}*/
