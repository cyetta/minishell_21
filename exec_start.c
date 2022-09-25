/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 20:10:42 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/25 22:24:08 by cyetta           ###   ########.fr       */
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
#include "ft_signal.h"

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
собирает запущенные дочки и для последней запущенной забирает 
errorlevel
*/
void	collect_cmd(t_mshell *data, pid_t last_pid)
{
	int		status;
	int		t_pid;

	t_pid = wait(&status);
	while (t_pid != -1)
	{
		if (WIFEXITED(status) && t_pid == last_pid)
			data->errlvl = WEXITSTATUS(status);
		t_pid = wait(&status);
	}
}

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
Основной цикл запуска команд
*/
int	exec_start(t_mshell *data)
{
	t_list	*cmd;
	t_list	*prevcmd;
	pid_t	last_pid;

	ft_lstiter(data->exec_lst, exec_createpath);
	cmd = data->exec_lst;
	prevcmd = NULL;
	last_pid = 0;
	while (cmd)
	{
		if (cmd_in_pipe(get_execmd(prevcmd), get_execmd(cmd)))
			last_pid = lunch_pipe(get_execmd(prevcmd), get_execmd(cmd));
		else
			last_pid = lunch_standalone(get_execmd(cmd));
		prevcmd = cmd;
		cmd = cmd->next;
	}
	collect_cmd(data, last_pid);
	return (ERR_OK);
}
