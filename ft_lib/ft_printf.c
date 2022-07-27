/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 17:37:51 by cyetta            #+#    #+#             */
/*   Updated: 2022/02/22 22:41:50 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"

static void	flag_init(t_flag *fl)
{
	fl->f_minus = 0;
	fl->f_null = 0;
	fl->f_point = 0;
	fl->f_prec = 0;
	fl->f_width = 0;
}

/*
function manage the following conversions: cspdiuxX%
and parse flag '-0.' and mininal field
*/
int	ft_printf(const char *str, ...)
{
	int		str_cnt;
	int		str_idx;
	t_flag	str_flag;
	va_list	arg;

	if (!str)
		return (-1);
	va_start(arg, str);
	str_cnt = 0;
	str_idx = -1;
	while (str[++str_idx] != '\0')
	{
		if (str[str_idx] == '%')
		{
			flag_init(&str_flag);
			str_cnt += ft_parse_flag(str, &str_idx, &str_flag, arg);
			continue ;
		}
		write(1, str + str_idx, 1);
		str_cnt++;
	}
	va_end(arg);
	return (str_cnt);
}
