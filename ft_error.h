/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:03:23 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/25 22:25:42 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H
# define ERR_OK 0
# define ERR_USAGE 1
# define ERR_ATOI_NOTVALUE 2
# define ERR_ATOI_OVER 3
# define ERR_INIT_4 4
# define ERR_INIT_5 5
# define ERR_MALLOC 6
# define ERR_SYNTAX 7
# define ERR_SYNTAX_OPNQUOTES 8
# define ERR_SYNTAX_PIPE 9
# define ERR_SYNTAX_RDR 10
# define ERR_SYNTAX_RDR_IN 11
# define ERR_SYNTAX_RDR_OUT 12
# define ERR_SYNTAX_RDR_DOUT 13
# define ERR_SYNTAX_RDR_HDOC 14
# define ERR_NOFILESFOUND 15
# define ERR_TMPFILEACCCESERR 16
# define ERR_SYNTAX_ERRNO 17
# define ERR_EMPTYCMD 18
# define ERR_CTRLD_QUIT 19
# define ERR_LASTERR ERR_EMPTYCMD

int	err_prnt3n(const char *msg1, const char *msg2, const char *msg3, int err);
int	err_msg(const char *msg, int err);
int	ft_error(int errnum);
int	is_syntax_err(int err);
#endif
