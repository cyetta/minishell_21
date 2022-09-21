/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_lnch_standalone.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 23:13:20 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/19 23:59:39 by cyetta           ###   ########.fr       */
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
Сохраняем стандартные потоки и устанавливаем редиректы, не в пайпе
*/
void	stdaln_rdrsave(t_prgexec *cmd, int *stdin, int *stdout)
{
	if (cmd->f_stdin > 2)
	{
		*stdin = dup(0);
		dup2(cmd->f_stdin, 0);
	}
	if (cmd->f_stout > 2)
	{
		*stdout = dup(1);
		dup2(cmd->f_stout, 1);
	}
}

/*
Восстанавливаем стандартные потоки и закрываем редиректы, не в пайпе
*/
void	stdaln_rdrrestore(t_prgexec *cmd, int *stdin, int *stdout)
{
	if (cmd->f_stdin > 2)
	{
		close(cmd->f_stdin);
		cmd->f_stdin = 0;
		dup2(*stdin, 0);
	}
	if (cmd->f_stout > 2)
	{
		close(cmd->f_stout);
		cmd->f_stout = 0;
		dup2(*stdout, 1);
	}
}

/*
Запуск одной внешней, не в пайпе, программы
*/
void	stdaln_runextr(t_prgexec *cmd)
{
	if (cmd->execmd)
	{
		cmd->cmd_pid = fork();
		if (cmd->cmd_pid == -1)
			exit (err_prnt3n("minishell standalon", cmd->execmd, \
			strerror(errno), ERR_SYNTAX_ERRNO));
		else if (!cmd->cmd_pid)
		{
			execve(cmd->execmd, cmd->argv, cmd->mdata->a_env);
			exit (err_prnt3n("minishell", cmd->execmd, \
			strerror(errno), 127));
		}
	}
}

/*
Исполняет одну команду, не в пайпе.
*/
void	lunch_standalone(t_prgexec *cmd)
{
	int	stdin;
	int	stdout;
	int	bnum;

	if (open_rdr(cmd))
		return ;
	stdaln_rdrsave(cmd, &stdin, &stdout);
	bnum = is_builtin(cmd);
	if (bnum)
		cmd->mdata->errlvl = runbuiltin(cmd, bnum);
	else
		stdaln_runextr(cmd);
	stdaln_rdrrestore(cmd, &stdin, &stdout);
}