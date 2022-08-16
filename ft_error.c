/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:02:36 by cyetta            #+#    #+#             */
/*   Updated: 2022/08/17 01:30:56 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "ft_error.h"
#include "ft_lib/libft.h"

static int	err_prnt(const char *msg, int err)
{
	write(2, msg, ft_strlen(msg));
	return (err);
}

//	printf("%s %d\n", msg, err);
int	err_msg(const char *msg, int err)
{
	char	*num;

	err_prnt(msg, err);
	num = ft_itoa(err);
	if (num)
	{
		write(2, num, ft_strlen(num));
		free(num);
	}
	write(2, "\n", 1);
	return (err);
}

/*
returns ERR_SYNTAX if the error is in a set of syntax errors
*/
int	is_syntax_err(int err)
{
	if (err >= ERR_SYNTAX && err < ERR_EMPTYCMD)
		return (ERR_SYNTAX);
	return (err);
}

int	ft_error(int errnum)
{
	const char	*msg[] = {"", "Usage: ./minishell \n No argument needed.\n", \
	"Not value. Error ", "Value overflow. Error ", "Initialization error ", \
	"Initialization error ", "Memory allocation error ", "Error syntax error", \
	"Open quotes error ", "Syntax error, unexpected token \'|\'. Error ", \
	"Syntax error, unexpected token \'newline\'. Error ", \
	"Syntax error, unexpected token \'<\'. Error ", \
	"Syntax error, unexpected token \'>\'. Error ", \
	"Syntax error, unexpected token \'>>\'. Error ", \
	"Syntax error, unexpected token \'<<\'. Error ", \
	"No commands. Empty line "};

	if (errnum == ERR_USAGE)
		return (err_prnt(msg[errnum], errnum));
	else if (errnum > ERR_USAGE && errnum <= ERR_LASTERR)
		return (err_msg(msg[errnum], errnum));
	else
		return (err_msg("Unknown error ", errnum));
}
