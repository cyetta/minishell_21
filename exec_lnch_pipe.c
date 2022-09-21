/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_lnch_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 23:13:20 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/21 22:23:51 by cyetta           ###   ########.fr       */
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

int	close_pipe(t_prgexec *prevcmd, t_prgexec *cmd, int err)
{
	if (prevcmd && prevcmd->is_pipe)
	{
		close(prevcmd->pipe[1]);
		close(prevcmd->pipe[0]);
	}
	if (cmd->is_pipe)
	{
		close(cmd->pipe[1]);
		close(cmd->pipe[0]);
	}
	if (cmd->f_stdin > 2)
	{
		close(cmd->f_stdin);
		cmd->f_stdin = 0;
	}
	if (cmd->f_stout > 2)
	{
		close(cmd->f_stout);
		cmd->f_stout = 0;
	}
	return (err);
}

void	redir_pipe(t_prgexec *prevcmd, t_prgexec *cmd)
{
	if (cmd->f_stdin > 2)
		dup2(cmd->f_stdin, 0);
	else if (prevcmd && prevcmd->is_pipe)
		dup2(prevcmd->pipe[0], 0);
	if (cmd->f_stout > 2)
		dup2(cmd->f_stout, 1);
	else if (cmd->is_pipe)
		dup2(cmd->pipe[1], 1);
}

int	exec_pipe(t_prgexec *cmd)
{
	int	err;
	int	bnum;

	err = 127;
	bnum = is_builtin(cmd);
	if (bnum)
		err = runbuiltin(cmd, bnum);
	else
	{
		execve(cmd->execmd, cmd->argv, cmd->mdata->a_env);
		err_prnt3n("minishell", cmd->execmd, \
	strerror(errno), err);
	}
	close(0);
	close(1);
	return (err);
}

/*
запускает трубу из предыдущей и текущей команды.
prevcmd может быть NULL, что означает что комада первая.
cmd не может быть NULL.
возвращает PID запущенного процесса
*/
int	lunch_pipe(t_prgexec *prevcmd, t_prgexec *cmd)
{
	if (cmd->is_pipe)
		pipe(cmd->pipe);
	cmd->cmd_pid = fork();
	if (cmd->cmd_pid == -1)
		exit (err_prnt3n("minishell pipe", cmd->execmd, \
		strerror(errno), ERR_SYNTAX_ERRNO));
	else if (cmd->cmd_pid)
	{
		if (prevcmd && prevcmd->is_pipe)
			close(prevcmd->pipe[0]);
		if (cmd->is_pipe)
			close(cmd->pipe[1]);
		return (cmd->cmd_pid);
	}
	if (open_rdr(cmd))
		exit (close_pipe(prevcmd, cmd, 1));
	redir_pipe(prevcmd, cmd);
	close_pipe(prevcmd, cmd, 1);
	exit (exec_pipe(cmd));
}