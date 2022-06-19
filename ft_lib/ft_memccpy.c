/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 22:32:54 by cyetta            #+#    #+#             */
/*   Updated: 2022/02/22 23:18:36 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
/*
The memccpy() function copies bytes from src to dest, up to and including the
first occurrence of the character c, or until cnt bytes have been copied,
whichever comes first.
Returns: A pointer to the byte in dest following the character c,
if one is found and copied; otherwise, NULL.
*/
void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	i;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = -1;
	while (++i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		if (((unsigned char *)src)[i] == (unsigned char)c)
			return ((void *)&((char *)dst)[i + 1]);
	}
	return (NULL);
}
