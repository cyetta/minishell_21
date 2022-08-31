/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 20:10:42 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/01 02:26:12 by cyetta           ###   ########.fr       */
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
инит для обхода 25 строк
*/
static char	*findexecbypathinit(char *cmd, char	**a_path, char *vpath)
{
	char	*t;

	a_path = ft_split(vpath, ':');
	if (!a_path)
		exit(ft_error(ERR_MALLOC));
	t = ft_strjoin("/", cmd);
	if (!t)
		exit(ft_error(ERR_MALLOC));
	return (t);
}

/*
return для обхода 25 строк
*/
static char	*findexecbypathret(int err, char *cmd, char *ret)
{
	if (err == ERR_NOFILESFOUND)
		err_prnt3n("minishell", cmd, " command not found", ERR_NOFILESFOUND);
	else if (err == ERR_OK)
		return (ret);
	else if (err == ERR_SYNTAX_ERRNO)
		free(ret);
	return (NULL);
}

/*
ищет команду в переменной окружения $PATH,
команда не должна быть по абсолютному или относительному пути
возвращает абсолютный путь к команде, если он существует
или NULL если команда не найдена.
если ошибка или команда не найдена выводит сообщение
*/
char	*findexecbypath(char *cmd, char *vpath)
{
	char	**a_path;
	char	*t;
	char	*ret;
	int		i;
	int		err;

	t = findexecbypathinit(cmd, a_path, vpath);
	i = -1;
	while (a_path[++i])
	{
		ret = ft_strjoin(a_path[i], t);
		if (!ret)
			exit(ft_error(ERR_MALLOC));
		err = is_cmd_exist(ret);
		if (err != ERR_NOFILESFOUND)
			break ;
		free(ret);
		free(a_path[i]);
	}
	free(t);
	free(a_path);
	return (findexecbypathret(err, cmd, ret));
}

/*
check for exist command in content
return 0 if command exit
return 1 if command not exist
*/
int	checkpath(void *key, void *content)
{
	t_mshell	*data;
	t_prgexec	*cmd;

	data = (t_mshell *)key;
	cmd = (t_prgexec *)content;
	if (is_builtin(cmd->argv[0]))
		return (0);
	if (!ft_strrchr(cmd->argv[0], '/'))
		return (findbypath(cmd->argv[0], data->a_env));
	return (1);
}

int	exec_checkcmd(t_mshell *data)
{
	t_prgexec	*err_cmd;

	err_cmd = ft_lstsearch(data->exec_lst, data, checkpath);
	return (ERR_OK);
}
