/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_dec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 20:39:01 by cyetta            #+#    #+#             */
/*   Updated: 2022/02/22 22:43:16 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"

static int	ft_utoxsz(char **s, unsigned long long n, int base, t_flag *s_flag)
{
	int	size;

	size = 0;
	if (n == 0 && s_flag->f_prec > 0)
		size = s_flag->f_prec;
	else if (n == 0)
		++size;
	else
	{
		while (n)
		{
			++size;
			n = n / base;
		}
		if (s_flag->f_point && s_flag->f_prec > size)
			size = s_flag->f_prec;
		else
			s_flag->f_prec = size;
	}
	*s = malloc(sizeof(char) * (size + 1));
	if (!(*s))
		return (size);
	(*s)[size] = '\0';
	return (size);
}

/*
Allocates (with malloc(3)) and returns a string representing the unsigned
integer received as an argument.
n - the integer to convert.
Return: The string representing the integer. NULL if the allocation fails.
*/
char	*ft_utoabase(unsigned long long n, char *base, t_flag *str_flag)
{
	char	*str;
	int		size;
	int		base_pw;

	base_pw = ft_strlen(base);
	size = ft_utoxsz(&str, n, base_pw, str_flag);
	if (!str)
		return (NULL);
	if (n == 0 && str_flag->f_point && str_flag->f_prec == 0)
		str[0] = 0;
	else
	{
		while (size)
		{
			if (n)
				str[--size] = base[(n % base_pw)];
			else
				str[--size] = '0';
			n = n / base_pw;
		}
	}
	return (str);
}

int	ft_prn_udec(unsigned int a, t_flag *str_flag)
{
	char	*s;
	int		len;

	s = ft_utoabase(a, "0123456789", str_flag);
	if (!s)
		return (0);
	len = ft_prn_str(s, str_flag);
	free(s);
	return (len);
}

int	ft_prnwpref(const char *pref, char *uanum, t_flag *str_flag)
{
	char	*dest;
	int		i;
	int		s1_l;
	int		s2_l;

	s1_l = ft_strlen(pref);
	s2_l = ft_strlen(uanum);
	dest = malloc(sizeof(char) * (s1_l + s2_l + 1));
	if (!dest)
		return (0);
	i = -1;
	while (*pref)
		dest[++i] = *pref++;
	while (*uanum)
		dest[++i] = *uanum++;
	dest[++i] = 0;
	str_flag->f_prec += s1_l;
	i = ft_prn_str(dest, str_flag);
	free(dest);
	return (i);
}

int	ft_prn_dec(int a, t_flag *str_flag)
{
	char			*s;
	int				len;
	unsigned int	ua;

	ua = (unsigned int) a;
	if (a < 0)
		ua = (unsigned int)(-a);
	s = ft_utoabase(ua, "0123456789", str_flag);
	if (!s)
		return (0);
	if (a >= 0)
		len = ft_prn_str(s, str_flag);
	else if (str_flag->f_null)
	{
		str_flag->f_width--;
		len = write(1, "-", 1) + ft_prn_str(s, str_flag);
	}
	else
		len = ft_prnwpref("-", s, str_flag);
	free(s);
	return (len);
}
