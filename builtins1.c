/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:21:39 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/10 23:32:40 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_util.h"
#include "builtins.h"

/*
Check command for builtin
return builtin number or 0
*/
int	is_builtin(t_prgexec *cmd)
{
	static char	*bltin = "echo    cd      pwd     export  unset   env     exit";
	char		*subs;

	subs = ft_strnstr(bltin, cmd->argv[0], ft_strlen(bltin));
	if (subs)
		return (((subs - bltin) >> 3) + 1);
	return (0);
}

/*
echo with option -n
*/
int	builtin_echo(t_prgexec *cmd)
{
	printf("this is %s\n", cmd->execmd);
	return (0);
}

/*
cd with only a relative or absolute path
 */
int	builtin_cd(t_prgexec *cmd)
{
	printf("this is %s\n", cmd->execmd);
	return (0);
}

/*
pwd with no options
 */
int	builtin_pwd(t_prgexec *cmd)
{
	printf("this is %s\n", cmd->execmd);
	return (0);
}
