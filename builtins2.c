/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:21:09 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/30 21:54:10 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "ft_util.h"
#include "builtins.h"
#include "ft_error.h"
#include "parser.h"
#include "lexer.h"

/*
unset with no options
unset [-fv] name ...
unset values and attributes of variables and functions
Each variable or function specified by name shall be unset.
 */
int	builtin_unset(t_prgexec *cmd)
{
	int		i;

	i = 0;
	while (cmd->argv[++i])
		del_env_var(&cmd->mdata->env_lst, cmd->argv[i]);
	return (ERR_OK);
}

/*
env with no options or arguments
env [-iv] [-P altpath] [-S string] [-u name] [name=val ...] [utility [arg ...]]
The env utility executes another utility after modifying the environment as
specified on the command line.  Each name=value option specifies the setting
of an environment variable, name, with a value of value.  All such environment
variables are set before the utility is executed.
 */
int	builtin_env(t_prgexec *cmd)
{
	int	i;

	if (cmd->argv[1])
		return (err_prnt3n("minishell", "env", "too many arguments", 1));
	i = 0;
	while (cmd->mdata->a_env[++i])
		printf("%s\n", cmd->mdata->a_env[i]);
	return (0);
}

/*
 exit with no options
 */
int	builtin_exit(t_prgexec *cmd)
{
	int	i;

	if (cmd->argv[1] && cmd->argv[2])
		return (err_prnt3n("minishell", "exit", "too many arguments", 1));
	if (!cmd->argv[1])
		exit(err_prnt3n("exit\n", NULL, NULL, 0));
	i = 0;
	if (cmd->argv[1][0] == '-')
		i = 1;
	while (ft_isdigit(cmd->argv[1][i]))
		i++;
	if (cmd->argv[1][i] != '\0' || i > 18 || (cmd->argv[1][0] == '-' && i == 1))
		exit (err_prnt3n("minishell: exit", cmd->argv[1], \
	"numeric argument required", 255));
	exit(err_prnt3n("exit\n", NULL, NULL, ft_atoi(cmd->argv[1]) % 256));
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
