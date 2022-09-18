/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_check_u.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 20:10:42 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/18 15:31:14 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_error.h"
#include "ft_util.h"
#include "minishell.h"
#include "executor.h"
#include "builtins.h"

/*
Возвращает(malloc) значение $PATH или значение по умолчанию если 
переменная не найдена или пустая
*/
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
проверяет существует ли команда по заданному пути
возвращает
ERR_OK - команда существует
ENOENT - команда не существует 
или другие ошибки если команда сущетсввует

ERR_NOFILESFOUND - команда не найдена, сообщений нет
ERR_SYNTAX_ERRNO - все остальные ошибки, +сообщение
*/
int	is_cmd_exist(char *cmd)
{
	int	err;

	if (!access(cmd, F_OK))
		return (ERR_OK);
	err
	else if (errno == ENOENT)
		return (ERR_NOFILESFOUND);
	err_prnt3n("minishell", cmd, strerror(errno), ERR_SYNTAX_ERRNO);
	return (ERR_SYNTAX_ERRNO);
}

/*
инит для обхода 25 строк
создание массива путей из переменной path,
Добавление / к команде, подразумевается что комада без путей
*/
static char	*findexecbypathinit(char *cmd, char	***a_path, char *vpath)
{
	char	*t;

	*a_path = ft_split(vpath, ':');
	if (!*a_path)
		exit(ft_error(ERR_MALLOC));
	t = ft_strjoin("/", cmd);
	if (!t)
		exit(ft_error(ERR_MALLOC));
	return (t);
}

/*
return для обхода 25 строк
проверка ошибок существования команды
*/
char	*findexecbypathret(int err, char *cmd, char *ret)
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
или ee же, если команда не найдена.
если ошибка или команда не найдена выводит сообщение
*/
char	*findexecbypath(char *cmd, char *vpath)
{
	char	**a_path;
	char	*t;
	char	*ret;
	int		i;
	int		err;

	t = findexecbypathinit(cmd, &a_path, vpath);
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
	}
	free(t);
	i = -1;
	while (a_path[++i])
		free(a_path[i]);
	free(a_path);
	return (findexecbypathret(err, cmd, ret));
}
