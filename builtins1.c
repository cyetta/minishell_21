/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:21:39 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/30 21:54:13 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "ft_util.h"
#include "builtins.h"
#include "minishell.h"
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
echo with option -n
*/
int	builtin_echo(t_prgexec *cmd)
{
	int	i;

	i = 1;
	if (!cmd->argv[1])
	{
		printf("\n");
		return (0);
	}
	while (cmd->argv[i] && !ft_strncmp(cmd->argv[i], "-n",
			ft_strlen(cmd->argv[i])))
		i++;
	while (cmd->argv[i])
	{
		printf("%s", cmd->argv[i]);
		if (cmd->argv[i + 1])
			printf(" ");
		i++;
	}
	if (ft_strncmp(cmd->argv[1], "-n", ft_strlen(cmd->argv[1])))
		printf("\n");
	return (0);
}

/*
change directory and set PWD OLDPWD
*/
int	cd_exec(char *path, t_ktable *pwd, t_ktable *oldpwd, t_list **env)
{
	char	*t_path;

	t_path = getcwd(NULL, 0);
	if (chdir(path))
	{
		free (t_path);
		return (err_prnt3n("minishell: cd", path, strerror(errno), 1));
	}
	if (!(pwd))
		add_env_var(env, "PWD", NULL);
	else if (pwd->value)
		free(pwd->value);
	pwd->value = getcwd(NULL, 0);
	if (!(oldpwd))
		add_env_var(env, "OLDPWD", NULL);
	else if (oldpwd->value)
		free(oldpwd->value);
	oldpwd->value = t_path;
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
	if (cmd->argv[2])
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
