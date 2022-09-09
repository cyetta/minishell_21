/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:21:39 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/09 18:13:56 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_util.h"
#include "builtins.h"

/*
if command is builtin execute and
return execute status
*/
int	is_builtin(t_prgexec *cmd)
{
	static char	*bltin = "echo   cd      pwd     export  unset   env     exit";
	char		*subs;

	subs = ft_strnstr(bltin, cmd->argv[0], ft_strlen(cmd));
	if (subs)
		return (((subs - bltin) >> 3) + 1);
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
