/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 18:58:24 by cyetta            #+#    #+#             */
/*   Updated: 2022/08/29 20:43:12 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_util.h"

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
int(*cmp)(void *key, void *content)
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

/*
	Delete node *node from list *root root with content.
	Content deleted by del_cntnt(void *content)
*/
void	ft_lstdelnode(t_list **root, t_list *node, void (*del_cntnt)(void *))
{
	t_list	*t;
	t_list	*prev;

	t = *root;
	if (!t || !node)
		return ;
	prev = NULL;
	while (t)
	{
		if (node == t)
		{
			if (prev == NULL)
				*root = t->next;
			else
				prev->next = t->next;
			ft_lstdelone(t, del_cntnt);
			return ;
		}
		prev = t;
		t = t->next;
	}
}

/*
	Insert node *new before node *node in the list **root
*/
void	ft_lstinsbeforenode(t_list **root, t_list *node, t_list *new)
{
	t_list	*t;
	t_list	*prev;

	t = *root;
	if (t && node)
	{
		prev = NULL;
		while (t)
		{
			if (node == t)
			{
				if (prev == NULL)
					*root = new;
				else
					prev->next = new;
				new->next = t;
				return ;
			}
			prev = t;
			t = t->next;
		}
	}
	else if (!t)
		*root = new;
}

/*
	Insert node *new after node *node in the list **root
*/
void	ft_lstinsafternode(t_list **root, t_list *node, t_list *new)
{
	t_list	*t;

	t = *root;
	if (t && node)
	{
		while (t)
		{
			if (node == t)
			{
				new->next = t->next;
				t->next = new;
				return ;
			}
			t = t->next;
		}
	}
	else if (!t)
		*root = new;
}
