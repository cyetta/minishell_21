/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 20:10:42 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/10 19:37:07 by cyetta           ###   ########.fr       */
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

/* Ошибка в обработке редиректов. Баш при обработке редиректов запускает команды
и ошибку выдает в процессе обработки команды т.е. если предыдущие команды
отработали шттано то  в редиректы запишется вывод
Нужно переделывать exec_check.c и в екзек передавать список файлов для редиректа
которые будут открыты при исполении команд
*/
/*
настриваем пайпы и редиректы для текущей и предыдущей команды
если предыдущая NULL, значит команда первая.
редиректы в приорете над пайпом.
*/
void	setredir(t_prgexec *prevcmd, t_prgexec *cmd)
{
	if (cmd->is_pipe && !prevcmd)
		return ;
	else if (cmd->is_pipe && prevcmd)
		return ;
}

/*
обраная функция. разбирает пайп
*/
void	unsetredir(t_prgexec *prevcmd, t_prgexec *cmd)
{
	(void)prevcmd;
	if (cmd->is_pipe)
		return ;
}

/*
запускает билдин,
возвращает 0 если это не билдин
*/
int	runbuildin(t_prgexec *cmd)
{
	int	bnum;

	bnum = is_builtin(cmd);
	if (bnum)
		printf("Execute builtin number %d\n", bnum);
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
		if (!prevcmd)
			setredir(NULL, (t_prgexec *)cmd->content);
		else
			setredir((t_prgexec *)prevcmd->content, (t_prgexec *)cmd->content);
		if (!runbuildin((t_prgexec *)cmd->content))
			err = runexternal((t_prgexec *)cmd->content);
		prevcmd = cmd;
		cmd = cmd->next;
	}
	err++;
	collect_cmd(data);
	return (ERR_OK);
}
