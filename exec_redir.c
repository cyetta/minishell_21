/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:34:21 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/14 01:35:11 by cyetta           ###   ########.fr       */
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
int	setredir(t_prgexec *prevcmd, t_prgexec *cmd)
{
	if (cmd->is_pipe && !prevcmd)
		return ;
	else if (cmd->is_pipe && prevcmd)
		return (ERR_OK);
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
