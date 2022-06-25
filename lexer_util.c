/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:52:13 by cyetta            #+#    #+#             */
/*   Updated: 2022/06/25 20:15:20 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
Returns true if ch in reserved character list
*/
int	is_reserved(char ch)
{
	const char	reserved[] = "\'\"$|<>";

	if (ft_isspace(ch))
		return (1);
	if (ft_strchr(reserved, ch))
		return (1);
	return (0);
}

/*
Returns substring from position pos, limited by reserved
character or \0,see also is_reserved().
if malloc() error, return NULL.
Position pos increment by length of substring
*/
char	*get_subs(char *str, int *pos)
{
	int		subslen;
	char	*dest;

	subslen = 1;
	while (!is_reserved(str[*pos + subslen]) && str[*pos + subslen])
		subslen++;
	dest = ft_substr(str, *pos, subslen);
	*pos += subslen;
	return (dest);
}
