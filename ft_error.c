/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:02:36 by cyetta            #+#    #+#             */
/*   Updated: 2022/08/21 20:44:08 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include "ft_error.h"
#include "ft_lib/libft.h"

int	err_prnt3n(const char *msg1, const char *msg2, const char *msg3, int err)
{
	if (!msg1)
		return (err);
	write(2, msg1, ft_strlen(msg1));
	if (!msg2)
		return (err);
	write(2, ": ", 2);
	write(2, msg2, ft_strlen(msg2));
	if (!msg3)
		return (err);
	write(2, ": ", 2);
	write(2, msg3, ft_strlen(msg3));
	write(2, "\n", 1);
	return (err);
}

int	err_msg(const char *msg, int err)
{
	char	*num;

	err_prnt3n("minishell", msg, NULL, err);
	num = NULL;
	if (err >= 0)
	{
		num = ft_itoa(err);
		if (num)
		{
			write(2, " Error ", 7);
			write(2, num, ft_strlen(num));
			free(num);
		}
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
	"Atoi not value.", "Atoi value overflow.", "Initialization error.", \
	"Initialization error ", "Memory allocation error ", "Syntax error ", \
	"Open quotes error.", "Syntax error, unexpected token \'|\'.", \
	"Syntax error, unexpected token \'newline\'.", \
	"Syntax error, unexpected token \'<\'.", \
	"Syntax error, unexpected token \'>\'.", \
	"Syntax error, unexpected token \'>>\'.", \
	"Syntax error, unexpected token \'<<\'.", \
	"No file or directory found.", "File or directory access error.", \
	"", "No commands. Empty line."};

	if (errnum == ERR_USAGE)
		return (err_prnt3n(msg[errnum], NULL, NULL, errnum));
	else if (errnum == ERR_SYNTAX_ERRNO)
		return (errnum);
	else if (errnum > ERR_USAGE && errnum <= ERR_LASTERR)
		return (err_msg(msg[errnum], errnum));
	else
		return (err_msg("Unknown error ", errnum));
}
