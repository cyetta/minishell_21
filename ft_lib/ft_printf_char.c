/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 20:39:01 by cyetta            #+#    #+#             */
/*   Updated: 2022/02/22 22:42:08 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"

int	ft_write_sp(char symb, int n)
{
	int	i;

	if (n < 1)
		return (0);
	i = n;
	while (i--)
		write(1, &symb, 1);
	return (n);
}

int	ft_prn_char(int a, t_flag *str_flag)
{
	char	c;

	c = (char)a;
	if (str_flag->f_width >= 1)
		str_flag->f_width -= 1;
	if (str_flag->f_minus)
		return (write(1, &c, 1) + ft_write_sp(' ', str_flag->f_width));
	else
		return (ft_write_sp(' ', str_flag->f_width) + write(1, &c, 1));
}

int	ft_prn_str(char *s, t_flag *str_flag)
{
	char	*s_out;
	int		s_len;
	char	space;

	s_out = s;
	if (!s)
		s_out = "(null)";
	s_len = ft_strlen(s_out);
	if (str_flag->f_point && str_flag->f_prec >= 0 && s_len >= str_flag->f_prec)
		s_len = str_flag->f_prec;
	else if (str_flag->f_point && str_flag->f_prec < 0)
		return (ft_write_sp(' ', -str_flag->f_prec));
	if (str_flag->f_width > s_len)
		str_flag->f_width -= s_len;
	else
		str_flag->f_width = 0;
	space = ' ';
	if (str_flag->f_null)
		space = '0';
	if (str_flag->f_minus)
		return (write(1, s_out, s_len) + ft_write_sp(space, str_flag->f_width));
	else
		return (ft_write_sp(space, str_flag->f_width) + write(1, s_out, s_len));
}
