/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 17:02:14 by cyetta            #+#    #+#             */
/*   Updated: 2022/02/22 22:46:19 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>

typedef struct s_flag
{
	int	f_minus;
	int	f_null;
	int	f_point;
	int	f_width;
	int	f_prec;
}	t_flag;

int		ft_write_sp(char symb, int n);
int		ft_prn_char(int c, t_flag *str_flag);
int		ft_prn_str(char *s, t_flag *str_flag);
int		ft_prn_dec(int a, t_flag *str_flag);
int		ft_prn_udec(unsigned int a, t_flag *str_flag);
int		ft_prnwpref(const char *pref, char *uanum, t_flag *str_flag);
char	*ft_utoabase(unsigned long long n, char *base, t_flag *str_flag);
int		ft_prn_uhex(unsigned int a, t_flag *str_flag);
int		ft_prn_uuhex(unsigned int a, t_flag *str_flag);
int		ft_prn_ptr(unsigned long long a, t_flag *str_flag);
int		ft_parse_flag(const char *str, int *str_idx, t_flag *str_flag, \
						va_list arg);

#endif
