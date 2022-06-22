/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 18:30:44 by cyetta            #+#    #+#             */
/*   Updated: 2022/06/22 19:46:58 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
The strcmp() and strncmp() functions lexicographically compare the null-
terminated strings s1 and s2.
Because strcmp() is designed for comparing strings rather than binary data,
characters that appear after a `\0' character are not compared.
RETURN VALUES
The strcmp() and strncmp() functions return an integer greater than, equal to,
or less than 0, according as the string s1 is greater than, equal to, or less
than the string s2.  The comparison is done using unsigned characters, so that
`\200' is greater than `\0'.
*/
int	ft_strcmp(const char *s1, const char *s2)
{
	int	res;

	while (*s1 != '\0' && *s2 != '\0')
	{
		res = (*(unsigned char *)s1 - *(unsigned char *)s2);
		if (res)
			return (res);
		s1++;
		s2++;
	}
	res = (*(unsigned char *)s1 - *(unsigned char *)s2);
	return (res);
}

/*
Apply the cmp(key, lst->content) function to the contents of the list
until it returns true
returns a pointer to the content on the first equality
or NULL, if nothing finded
*/
void	*ft_lstsearch(t_list *lst, void *key, int (*cmp)(void *, void *))
{
	while (lst)
	{
		if ((*cmp)(key, lst->content))
			return (lst->content);
		lst = lst->next;
	}
	return (NULL);
}
