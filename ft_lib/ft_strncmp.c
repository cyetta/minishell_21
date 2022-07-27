/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 13:11:06 by cyetta            #+#    #+#             */
/*   Updated: 2022/03/25 17:05:27 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
/*
The strcmp() and strncmp() functions lexicographically compare the null-
terminated strings s1 and s2.

The strncmp() function compares not more than n characters.  Because
strncmp() is designed for comparing strings rather than binary data,
characters that appear after a `\0' character are not compared.

RETURN VALUES
The strcmp() and strncmp() functions return an integer greater than,
equal to, or less than 0, according as the string s1 is greater than,
equal to, or less than the string s2.  The comparison is done using
unsigned characters, so that `\200' is greater than `\0'.
*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	res;

	if (!n)
		return (0);
	while (*s1 != '\0' && *s2 != '\0' && n--)
	{
		res = (*(unsigned char *)s1 - *(unsigned char *)s2);
		if (res)
			return (res);
		if (!n)
			return (0);
		s1++;
		s2++;
	}
	res = (*(unsigned char *)s1 - *(unsigned char *)s2);
	return (res);
}
