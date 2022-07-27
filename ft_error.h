/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:03:23 by cyetta            #+#    #+#             */
/*   Updated: 2022/06/26 21:18:17 by cyetta           ###   ########.fr       */
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
# define ERR_OPNQUOTES 8
# define ERR_EMPTYCMD 9
# define ERR_LASTERR ERR_EMPTYCMD

int	ft_error(int errnum);
int	is_syntax_err(int err);
#endif
