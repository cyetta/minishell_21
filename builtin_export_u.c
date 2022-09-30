/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_u.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:21:09 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/30 16:21:38 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "ft_util.h"
#include "builtins.h"
#include "ft_error.h"
#include "parser.h"
#include "lexer.h"

int	ktblitm_low(void *key, void *content)
{
	t_ktable	*t_key;
	t_ktable	*t_content;

	t_key = (t_ktable *)key;
	t_content = (t_ktable *)content;
	if (ft_strcmp(t_key->key, t_content->key) >= 0)
		return (0);
	return (1);
}

void	b_export_delsorted(void *content)
{
	(void)content;
}

void	b_export_print(void *content)
{
	t_ktable	*t_content;

	t_content = (t_ktable *)content;
	if (t_content->value)
		printf("declare -x %s=\"%s\"\n", t_content->key, t_content->value);
	else
		printf("declare -x %s\n", t_content->key);
}
