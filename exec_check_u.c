/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_check_u.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 20:10:42 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/30 21:41:50 by cyetta           ###   ########.fr       */
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
Returns (malloc) the value of $PATH or the default value
".:/usr/bin:/bin" if no variable is found or empty
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
checks if the command exists on the specified path
returns
ERR_OK - command file exists
ENOENT - command file does not exist
or other errno errors if the command exists but is accessed with an error
*/
int	is_cmd_exist(char *cmd)
{
	if (!access(cmd, F_OK))
		return (ERR_OK);
	return (errno);
}

/*
init for bypass 25 lines limit
Creates an array of paths from the path variable,
Adding / to the command, assuming the command has no paths
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
return to bypass the 25 lines limit
If all goes well, it returns a new path to the command at path
Otherwise duplicate command
*/
char	*findexecbypathret(int err, char *cmd, char **ret)
{
	if (err == ERR_OK)
		return (*ret);
	if (err != ENOENT)
		free(*ret);
	*ret = ft_strdup(cmd);
	if (!(*ret))
		exit(ft_error(ERR_MALLOC));
	return (*ret);
}

/*
looks for a command in the $PATH environment variable,
command does not have to be in absolute or relative path
returns the absolute path to the command if it exists
or the same if no command is found.
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
		if (err != ENOENT)
			break ;
		free(ret);
	}
	free(t);
	i = -1;
	while (a_path[++i])
		free(a_path[i]);
	free(a_path);
	return (findexecbypathret(err, cmd, &ret));
}
