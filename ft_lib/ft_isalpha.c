/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:33:29 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/30 03:16:55 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Checking for letters A-Z, a-z
Returns 1 for letters, and 0 otherwise
*/
int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}
