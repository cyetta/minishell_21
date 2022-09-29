/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:21:09 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/29 21:04:35 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "ft_util.h"
#include "builtins.h"
#include "ft_error.h"

/*
export with no options
set the export attribute for variables
export name[=word]...
The shell shall give the export attribute to the variables corresponding to the
specified names, which shall cause them to be in the environment of subsequently
executed commands. If the name of a variable is followed by = word, then the
value of that variable shall be set to word.
 */
int	builtin_export(t_prgexec *cmd)
{
	printf("this is %s\n", cmd->execmd);
	return (0);
}

/*
unset with no options
unset [-fv] name ...
unset values and attributes of variables and functions
Each variable or function specified by name shall be unset.
 */
int	builtin_unset(t_prgexec *cmd)
{
	//t_ktable	*target;
	int			exit_code;

	exit_code = EXIT_SUCCESS;
	if (!*(cmd->argv + 1))
		return (exit_code);
	cmd->argv++;
	while (*cmd->argv)
	{
		if (check_option(*cmd->argv) == EXIT_FAILURE)
			exit_code = throw_error_usage("unset", *cmd->argv) + 1;
		else if (ft_strchr(*cmd->argv, '='))
			exit_code = throw_error_env("unset", *cmd->argv);
		else if (valid_env_name(*cmd->argv) == EXIT_FAILURE)
			exit_code = throw_error_env("unset", *cmd->argv);
		/*else
		{
			target = get_env(*cmd->argv);//get_env в процессе, думаю похожая функция есть в одном из файлом
			if (target)
				remove_env(target);// если таргет получился перемещаем на 1 и чистим
		}*/
		cmd->argv++;
	}
	return (exit_code);
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
