/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:02:36 by cyetta            #+#    #+#             */
/*   Updated: 2022/06/18 14:25:37 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_error.h"

static int	usage(int err)
{
	printf("Usage: ./minishell \n No argument needed.\n");
	return (err);
}

int	err_msg(const char *msg, int err)
{
	printf("%s %d\n", msg, err);
	return (err);
}

int	ft_error(int errnum)
{
	const char	*msg[] = {"", "Usage: ./minishell \n No argument needed.\n", \
	"Not value. Error ", "Value overflow. Error ", "Initialization error ", \
	"Initialization error ", "Memory allocation error ", "Error syntax error",\
	"Open quotes error "};

	if (errnum == ERR_USAGE)
		return (usage(ERR_USAGE));
	else if (errnum > ERR_USAGE && errnum <= ERR_OPNQUOTES)
		return (err_msg(msg[errnum], errnum));
	else
		return (err_msg("Unknown error ", errnum));
}
