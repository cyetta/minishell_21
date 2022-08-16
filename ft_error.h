/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:03:23 by cyetta            #+#    #+#             */
/*   Updated: 2022/08/17 01:31:07 by cyetta           ###   ########.fr       */
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
# define ERR_EMPTYCMD 15
# define ERR_LASTERR ERR_EMPTYCMD

int	ft_error(int errnum);
int	is_syntax_err(int err);
#endif
