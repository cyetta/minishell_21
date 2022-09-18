/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 20:10:42 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/18 04:47:20 by cyetta           ###   ########.fr       */
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
int	runbuildin(t_prgexec *cmd, int bnum)
{
	int					bnum;
	const t_bldin_func	a_bldin_f[] = {builtin_echo, builtin_cd, builtin_pwd, \
	builtin_export, builtin_unset, builtin_env, builtin_exit};

	return (a_bldin_f[bnum - 1](cmd));
}

/*
запускает внешнюю команду в новом процессе
*/
int	runexternal(t_prgexec *prevcmd, t_prgexec *cmd)
{
	(void)prevcmd;
	printf("Execute: %s\n", cmd->execmd);
	return (ERR_OK);
}

int	lunch_pipe(t_prgexec *prevcmd, t_prgexec *cmd)
{

}

int	lunch_standalone(t_prgexec *cmd)
{
	int	err;
	int	stdin;
	int	stdout;
	int	bnum;

	err = open_rdr(cmd);
	if (err)
		return (err);
	if (cmd->f_stdin > 2)
	{
		stdin = dup(0);
		dup2(cmd->f_stdin, 0);
	}
	if (cmd->f_stout > 2)
	{
		stdin = dup(1);
		dup2(cmd->f_stout, 1);
	}
	bnum = is_builtin(cmd);
	if (bnum)
		runbuildin(cmd, bnum);
	else if (cmd->execmd)
	{
		cmd->cmd_pid = fork();
		if (cmd->cmd_pid == -1)
			exit (err_prnt3n("minishell standalon", cmd->execmd, \
			strerror(errno), ERR_SYNTAX_ERRNO));
		else if (cmd->cmd_pid)
		{
			err = execve();
//// надо все перерабатывать
		}
	}
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
	else if (prevcmd && prevcmd->pipe)
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
	int		err;

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
	err++;
	collect_cmd(data);
	return (ERR_OK);
}
