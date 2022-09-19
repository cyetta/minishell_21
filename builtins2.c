/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:21:09 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/19 09:26:53 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_util.h"
#include "builtins.h"
#include "ft_error.h"
#include <stdlib.h>

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
	printf("this is %s\n", cmd->execmd);
	return (0);
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
	printf("this is %s\n", cmd->execmd);
	return (0);
}

/*
 exit with no options
 */
void	builtin_exit(t_prgexec *cmd)
{
	int	i;

	i = 0;
	if (cmd->argv[1] && cmd->argv[2])
		printf("exit\n");
	if (cmd->argv[1] && cmd->argv[2])
		err_msg("exit: too many arguments", 3);
	if (cmd->argv[1])
	{
		while (ft_isdigit(cmd->argv[1][i]))
			i++;
		if ((size_t)i != ft_strlen(cmd->argv[1]))
			err_msg("exit: numeric argument required", 3);
	}
	if (cmd->argv[1] && cmd->argv[2])
	{
		if (!cmd->argv[1])
			exit(0);
		else if ((size_t)i != ft_strlen(cmd->argv[1]))
			exit(255);
		else
			exit(ft_atoi(cmd->argv[1]) % 256);
	}
}
