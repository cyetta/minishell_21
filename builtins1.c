/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:21:39 by cyetta            #+#    #+#             */
/*   Updated: 2022/10/03 02:05:50 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "minishell.h"
#include "ft_util.h"
#include "builtins.h"
#include "parser.h"
#include "ft_error.h"

/*
Check command for builtin
Returns builtin number, count from 1. If no builtin found, return 0
*/
int	is_builtin(t_prgexec *cmd)
{
	static char	*bltin = "echo    cd      pwd     export  unset   env     exit";
	char		*subs;

	if (!cmd->argv[0])
		return (0);
	subs = ft_strnstr(bltin, cmd->argv[0], ft_strlen(bltin));
	if (subs)
		return (((subs - bltin) >> 3) + 1);
	return (0);
}

typedef int	(*t_bltin_func)(t_prgexec *);

/*
runs builtin with the number bnum, counting from 1,
bnum is result of is_builtin()
returns the result of builtin()
*/
int	runbuiltin(t_prgexec *cmd, int bnum)
{
	const t_bltin_func	a_bltin_f[] = {builtin_echo, builtin_cd, builtin_pwd, \
	builtin_export, builtin_unset, builtin_env, builtin_exit};

	return (a_bltin_f[bnum - 1](cmd));
}

/*
set PWD OLDPWD
*/
void	cd_setpwd(char *path, char *env_name, t_ktable *pwd, t_list **env)
{
	if (!pwd)
		add_env_var(env, env_name, path);
	else if (pwd->value)
		free(pwd->value);
	if (pwd)
		pwd->value = path;
	else if (path)
		free(path);
}

/*
change directory to path and set PWD OLDPWD
*/
int	cd_exec(char *path, t_ktable *pwd, t_ktable *oldpwd, t_list **env)
{
	char	*old_path;
	char	*new_path;

	old_path = getcwd(NULL, 0);
	if (chdir(path))
	{
		free (old_path);
		return (err_prnt3n("minishell: cd", path, strerror(errno), 1));
	}
	new_path = getcwd(NULL, 0);
	cd_setpwd(new_path, "PWD", pwd, env);
	cd_setpwd(old_path, "OLDPWD", oldpwd, env);
	return (0);
}

/*
cd with only a relative or absolute path
 */
int	builtin_cd(t_prgexec *cmd)
{
	t_ktable	*pwd;
	t_ktable	*oldpwd;

	oldpwd = search_env_var(cmd->mdata->env_lst, "OLDPWD");
	pwd = search_env_var(cmd->mdata->env_lst, "PWD");
	if (cmd->argv[1] && cmd->argv[2])
		return (err_prnt3n("minishell", "cd", "too many arguments", 1));
	else if (!cmd->argv[1] || (cmd->argv[1] && *(cmd->argv[1]) == '\0'))
		return (0);
	else if (cmd->argv[1][0] == '-' && cmd->argv[1][1] == '\0')
	{
		if (!oldpwd || (oldpwd && !oldpwd->value))
			return (err_prnt3n("minishell", "cd", \
		"OLDPWD variable not set", 1));
		return (cd_exec(oldpwd->value, pwd, oldpwd, &cmd->mdata->env_lst));
	}
	cd_exec(cmd->argv[1], pwd, oldpwd, &cmd->mdata->env_lst);
	return (0);
}
