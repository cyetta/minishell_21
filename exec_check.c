/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 20:10:42 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/21 01:34:01 by cyetta           ###   ########.fr       */
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

/*
Create (malloc) command execution string for execve. Not checked for bultin.
Returns absolute or relative path or NULL in case of error.
if there is an error, prints an error message
*/
char	*getexecpath(char *cmd, char **env)
{
	char	*ret;
	char	*path;

	if (!cmd)
		return (NULL);
	if (ft_strrchr(cmd, '/'))
	{
		ret = ft_strdup(cmd);
		if (!ret)
			exit(ft_error(ERR_MALLOC));
		return (ret);
	}
	else
	{
		path = get_path(env);
		ret = findexecbypath(cmd, path);
		free(path);
	}
	return (ret);
}

/*
Колбэк функция итератора обхода списка, формирует строку запуска команды
для работы execve() в t_prgexec.execmd
билтины и не найденные команды копируются как есть, если команд найдена
в $PATH, формируется абсолюный путь из $PATH и команды,
Если $PATH не найдена, используется дефолный путь ".:/usr/bin:/bin"
Пример:
	ft_lstiter(data->exec_lst, exec_createpath);
*/
void	exec_createpath(void *content)
{
	t_prgexec	*cmd;

	cmd = (t_prgexec *)content;
	if (is_builtin(cmd))
	{
		cmd->execmd = ft_strdup(cmd->argv[0]);
		if (!cmd->execmd)
			exit(ft_error(ERR_MALLOC));
	}
	else
		cmd->execmd = getexecpath(cmd->argv[0], cmd->mdata->a_env);
}

/*
Колбэк функция для поиска в списке элементов t_prgxec такого,
что t_prgexec->execmd равен key, в том числе и NULL
нужен для проверки есть ли неисполнимые команды
Пример:
if (ft_lstsearch(data->exec_lst, NULL, is_execmd))
 	return (ERR_SYNTAX_ERRNO);
*/
int	is_execmd(void *key, void *content)
{
	t_prgexec	*cmd;
	char		*cmdname;

	cmd = (t_prgexec *)content;
	cmdname = (char *)key;
	if (cmd && cmdname && cmd->execmd && !ft_strcmp(cmdname, cmd->execmd))
		return (1);
	else if (!cmd)
		return (0);
	else if (!cmdname && !cmd->execmd)
		return (1);
	return (0);
}
