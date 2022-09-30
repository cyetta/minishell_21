/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 17:34:44 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/30 03:18:28 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Checking for numbers 0-9
Returns 1 for numbers, and 0 otherwise
 */
int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	return (0);
}
