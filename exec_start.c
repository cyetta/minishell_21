/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 20:10:42 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/19 23:57:57 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "ft_error.h"
#include "ft_util.h"
#include "minishell.h"
#include "executor.h"
#include "builtins.h"

/*
Собирает выполненные дочки, устанавливает errorlevel по факту выполения
разбирает пайпы.

void	collect_cmd(t_mshell *data)
{
	(void)data;
}
*/

/*
Обертка, возвращает из листа списка контент - структуру prgexec.
или NULL если указатель листа NULL
*/
t_prgexec	*get_execmd(t_list *cmd)
{
	if (!cmd)
		return (NULL);
	return ((t_prgexec *)cmd->content);
}

/*
возвращает TRUE если cmd находится в пайпе, т.е. у текущей или предыдущей \
команды есть признак pipe, cmd - должна существовать!
если предыдущая комада NULL, значит cmd первая команда.
*/
int	cmd_in_pipe(t_prgexec *prevcmd, t_prgexec *cmd)
{
	if (cmd->is_pipe)
		return (1);
	else if (prevcmd && prevcmd->is_pipe)
		return (2);
	return (0);
}

/*
Основной цикл запуска команд
*/
int	exec_start(t_mshell *data)
{
	t_list	*cmd;
	t_list	*prevcmd;
	int		status;

	cmd = data->exec_lst;
	prevcmd = NULL;
	while (cmd)
	{
		if (cmd_in_pipe(get_execmd(prevcmd), get_execmd(cmd)))
			lunch_pipe(get_execmd(prevcmd), get_execmd(cmd));
		else
			lunch_standalone(get_execmd(cmd));
		prevcmd = cmd;
		cmd = cmd->next;
	}
	while (wait(&status) != -1)
	{
		if (WIFEXITED(status))
			data->errlvl = WEXITSTATUS(status);
	}
	return (ERR_OK);
}
//	collect_cmd(data);
