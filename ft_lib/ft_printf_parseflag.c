/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parseflag.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 20:39:50 by cyetta            #+#    #+#             */
/*   Updated: 2022/02/22 22:38:39 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"

static int	parse_type(const char *str, t_flag *str_flag, va_list arg)
{
	if (*str == '%')
		return (ft_prn_char('%', str_flag));
	else if (*str == 'c')
		return (ft_prn_char(va_arg(arg, int), str_flag));
	else if (*str == 's')
		return (ft_prn_str(va_arg(arg, char *), str_flag));
	else if (*str == 'd' || *str == 'i')
		return (ft_prn_dec(va_arg(arg, int), str_flag));
	else if (*str == 'u')
		return (ft_prn_udec(va_arg(arg, unsigned int), str_flag));
	else if (*str == 'x')
		return (ft_prn_uhex(va_arg(arg, unsigned int), str_flag));
	else if (*str == 'X')
		return (ft_prn_uuhex(va_arg(arg, unsigned int), str_flag));
	else if (*str == 'p')
		return (ft_prn_ptr(va_arg(arg, unsigned long long), str_flag));
	else
		return (write(1, str, 1));
}

static void	parse_fldig(const char *str, int *s_idx, int *pr_flag, \
							t_flag *s_flag)
{
	static int	dot_flag;

	if (!ft_isdigit(str[*pr_flag]))
		dot_flag = *pr_flag;
	*pr_flag = *s_idx;
	if (str[dot_flag] == '.')
		s_flag->f_prec = s_flag->f_prec * 10 + (int)(str[*s_idx] - '0');
	else
		s_flag->f_width = s_flag->f_width * 10 + (int)(str[*s_idx] - '0');
}

static void	set_flag_minus(int *s_idx, int *pr_flag, t_flag *s_flag)
{
	s_flag->f_minus = 1;
	s_flag->f_null = 0;
	s_flag->f_width = 0;
	*pr_flag = *s_idx;
}

static void	set_flag_dot(int *s_idx, int *pr_flag, t_flag *s_flag)
{
	s_flag->f_point = 1;
	s_flag->f_null = 0;
	s_flag->f_prec = 0;
	*pr_flag = *s_idx;
}

int	ft_parse_flag(const char *str, int *str_idx, t_flag *str_flag, \
						va_list arg)
{
	int	last_flag;

	last_flag = *str_idx;
	++(*str_idx);
	while ((str[*str_idx] != '\0'))
	{
		if (str[*str_idx] == '0' && str[last_flag] != '.' \
									&& !ft_isdigit(str[last_flag]))
			str_flag->f_null = 1;
		else if (str[*str_idx] == '-')
			set_flag_minus(str_idx, &last_flag, str_flag);
		else if (str[*str_idx] == '.')
			set_flag_dot(str_idx, &last_flag, str_flag);
		else if (ft_isdigit(str[*str_idx]))
			parse_fldig(str, str_idx, &last_flag, str_flag);
		else
		{
			if (str_flag->f_point || str_flag->f_minus)
				str_flag->f_null = 0;
			return (parse_type(&str[*str_idx], str_flag, arg));
		}
		++(*str_idx);
	}
	return (0);
}
