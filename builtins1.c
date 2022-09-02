/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:21:39 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/01 18:40:38 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_util.h"
/*
if command is builtin execute and
return execute status
*/
int	is_builtin(char *cmd)
{
	static char	*bltin = "echo cd pwd export unset env exit";
	char		*subs;

	subs = ft_strnstr(bltin, cmd, ft_strlen(cmd));
	if (subs)
		return (1);
	return (0);
}

/*
echo with option -n
*/
void	buitin_echo(void)
{
}

/*
cd with only a relative or absolute path
 */
void	buitin_cd(void)
{
}

/*
pwd with no options
 */
void	buitin_pwd(void)
{
}
