/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 20:10:42 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/01 21:25:25 by cyetta           ###   ########.fr       */
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
	int		err;

	if (ft_strrchr(cmd, '/'))
	{
		ret = ft_strdup(cmd);
		if (!ret)
			exit(ft_error(ERR_MALLOC));
		err = is_cmd_exist(ret);
		ret = findexecbypathret(err, cmd, ret);
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
Колбэк функция итератора обхода списка, формирует путь/команда для работы 
execve в t_prgexec.execmd
*/
void	exec_createpath(void *content)
{
	t_prgexec	*cmd;

	cmd = (t_prgexec *)content;
	if (is_builtin(cmd->argv[0]))
	{
		cmd->execmd = ft_strdup(cmd->argv[0]);
		if (!cmd->execmd)
			exit(ft_error(ERR_MALLOC));
	}
	else
		cmd->execmd = getexecpath(cmd->argv[0], cmd->mdata->a_env);
}

/*
Проверяет доступность команд в списке к запуску, если команда не доступна
в t_prgexec.execmd записывается NULL и выводится сообщение об ошибке 
или путь для запуска, абсолютный или относительный
при запуске NULL команды игнорируются
билдины записываются без пути
*/
int	exec_checkcmd(t_mshell *data)
{
	ft_lstiter(data->exec_lst, exec_createpath);
	return (ERR_OK);
}
