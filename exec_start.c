/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 20:10:42 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/14 01:36:15 by cyetta           ###   ########.fr       */
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

typedef int	(*t_bldin_func)(t_prgexec *);

/*
запускает билдин,
возвращает 0 если это не билдин
*/
int	runbuildin(t_prgexec *prevcmd, t_prgexec *cmd)
{
	int					bnum;
	const t_bldin_func	a_bldin_f[] = {builtin_echo, builtin_cd, builtin_pwd, \
	builtin_export, builtin_unset, builtin_env, builtin_exit};

	bnum = is_builtin(cmd);
	if (!bnum)
		return (bnum);
	if (cmd->is_pipe || (prevcmd && prevcmd->pipe))
	{
		printf("Execute builtin number %d in pipe\n", bnum);
		a_bldin_f[bnum - 1](cmd);
	}
	else
	{
		printf("Execute builtin number %d standalone\n ", bnum);
		a_bldin_f[bnum - 1](cmd);
	}
	return (bnum);
}

/*
запускает внешнюю команду в новом процессе
*/
int	runexternal(t_prgexec *cmd)
{
	printf("Execute: %s\n", cmd->execmd);
	return (ERR_OK);
}

/*
Собирает выполненные дочки, устанавливает errorlevel по факту выполения
разбирает пайпы.
*/
void	collect_cmd(t_mshell *data)
{
	(void)data;
}

/*
Обертка, возвращает из листа списка контент, структуру prgexec.
или NULL если указатель листа NULL
*/
t_prgexec	*get_execmd(t_list *cmd)
{
	if (!cmd)
		return (NULL);
	return ((t_prgexec *)cmd->content);
}

/*
Основной цикл запуска команд
*/
int	exec_start(t_mshell *data)
{
	t_list	*cmd;
	t_list	*prevcmd;
	int		err;

	cmd = data->exec_lst;
	prevcmd = NULL;
	while (cmd)
	{
		setredir(get_execmd(prevcmd), get_execmd(cmd));
		if (!runbuildin(get_execmd(prevcmd), get_execmd(cmd)))
			err = runexternal((t_prgexec *)cmd->content);
		prevcmd = cmd;
		cmd = cmd->next;
	}
	err++;
	collect_cmd(data);
	return (ERR_OK);
}
