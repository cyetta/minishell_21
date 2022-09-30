/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 20:10:42 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/30 21:36:19 by cyetta           ###   ########.fr       */
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
Callback function of list iterator, generates a command line to run execve()
in t_prgexec.exe. Builtin and not found commands are copied as is.
if a command is found in $PATH, the absolute path to command from $PATH is
generated. If $PATH is not found, the default path ".:/usr/bin:/bin" is used.
Example:
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
