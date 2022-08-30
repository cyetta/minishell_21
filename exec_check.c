/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 20:10:42 by cyetta            #+#    #+#             */
/*   Updated: 2022/08/30 03:21:08 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
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

	i=-1;
	while(env[++i])
		if(!ft_strncmp(env[i], "PATH", 4))
			break ;
	if(!env[i])
		path = ft_strdup(".:/usr/bin:/bin");
	else
	{
		p = ft_strchr(env[i], '=');
		if (!p || !*(p + 1))
			path = ft_strdup(".:/usr/bin:/bin");
		else
			path = ft_strdup(++p);
	}
	if(!path)
		exit(ft_error(ERR_MALLOC));
	return (path);
}

char	*findexecbypath(cmd, path)
{
	char	**a_path;
	char	*t;
	char	*ret;
	int		i;

	a_path = ft_split(path, ':');
	if (!a_path)
		exit(ft_error(ERR_MALLOC));
	t = ft_strjoin("/", cmd);
	if (!t)
		exit(ft_error(ERR_MALLOC));
	i = -1;
	while(a_path[++i])
	{
		ret = ft_strjoin(a_path[i], t);
		if (!t)
			exit(ft_error(ERR_MALLOC));
		if (!access(ret, X_OK))
			break;
		else if(errno == )
	}
	free(t);

}

/*
create(malloc) lunch string for execve
not checks for bultin
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

	return(ret);
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

}
