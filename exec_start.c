/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 20:10:42 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/30 21:10:12 by cyetta           ###   ########.fr       */
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
returns TRUE if cmd is in pipe, i.e. the current or previous
command has pipe sign, cmd must exist!
if the previous command is NULL, then cmd is the first command.
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
collects the running daughters and, for the last running one,
picks up errorlevel
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
Wrapper, returns content from list leaf, prgexec structure.
or NULL if leaf pointer is NULL
*/
t_prgexec	*get_execmd(t_list *cmd)
{
	if (!cmd)
		return (NULL);
	return ((t_prgexec *)cmd->content);
}

/*
command loop
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
