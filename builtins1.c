/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:21:39 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/19 23:52:02 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "ft_util.h"
#include "builtins.h"
#include "minishell.h"

/*
Check command for builtin
Return builtin number, count from 1. If no builtin found, return 0
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

typedef int	(*t_bldin_func)(t_prgexec *);

/*
запускает билдин с номером bnum, счет с 1,
bnum результат работы is_bultin()
возвращает результат работы билтина
*/
int	runbuiltin(t_prgexec *cmd, int bnum)
{
	const t_bldin_func	a_bldin_f[] = {builtin_echo, builtin_cd, builtin_pwd, \
	builtin_export, builtin_unset, builtin_env, builtin_exit};

	return (a_bldin_f[bnum - 1](cmd));
}

/* 	if (!ft_strncmp(cmd->argv[0], "exit", ft_strlen(cmd->argv[0])))
		builtin_exit(cmd);
	else if (!ft_strncmp(cmd->argv[0], "echo", ft_strlen(cmd->argv[0])))
		builtin_echo(cmd);
	else if (!ft_strncmp(cmd->argv[0], "pwd", ft_strlen(cmd->argv[0])))
	{
		builtin_pwd();
		printf("11234213412341234123412341234123412341234123\n");
	}
	else if (!ft_strncmp(cmd->argv[0], "env", ft_strlen(cmd->argv[0])))
		builtin_env(cmd);
	return (0); */

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
cd with only a relative or absolute path
 */
int	builtin_cd(t_prgexec *cmd)
{
	printf("this is %s\n", cmd->execmd);
	return (0);
}

/*
pwd with no options
 */
int	builtin_pwd(t_prgexec *cmd)
{
	char	pwd[4096];

	(void)cmd;
	getcwd(pwd, 4097);
	printf("%s\n", pwd);
	return (0);
}
