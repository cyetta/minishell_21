/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_check_u.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 20:10:42 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/01 02:24:55 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "ft_error.h"
#include "ft_util.h"
#include "minishell.h"
#include "executor.h"
#include "builtins.h"

char	*get_path(char **env)
{
	int		i;
	char	*path;
	char	*p;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], "PATH", 4))
			break ;
	if (!env[i])
		path = ft_strdup(".:/usr/bin:/bin");
	else
	{
		p = ft_strchr(env[i], '=');
		if (!p || !*(p + 1))
			path = ft_strdup(".:/usr/bin:/bin");
		else
			path = ft_strdup(++p);
	}
	if (!path)
		exit(ft_error(ERR_MALLOC));
	return (path);
}

/*
проверяет запускается ли команда по заданному пути
возвращает
ERR_OK - команда существует и запускается
ERR_NOFILESFOUND - команда не найдена, сообщений нет
ERR_SYNTAX_ERRNO - все остальные ошибки, +сообщение
*/
int	is_cmd_exist(char *cmd)
{
	if (!access(cmd, X_OK))
		return (ERR_OK);
	else if (errno == ENOENT)
		return (ERR_NOFILESFOUND);
	err_prnt3n("minishell", cmd, strerror(errno), ERR_SYNTAX_ERRNO);
	return (ERR_SYNTAX_ERRNO);
}

/*
create(malloc) lunch string for execve
not checks for bultin
return absolut or relative path
*/
char	*getexecpath(char *cmd, char **env)
{
	char	*ret;
	char	*path;

	if (ft_strrchr(cmd, '/'))
	{
		ret = ft_strdup(cmd);
		if (!ret)
			exit(ft_error(ERR_MALLOC));
	}
	else
	{
		path = get_path(env);
		ret = findexecbypath(cmd, path);
		free(path);
	}
	return (ret);
}
