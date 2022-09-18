/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:34:21 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/18 04:18:56 by cyetta           ###   ########.fr       */
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

/*
настриваем пайпы и редиректы для текущей и предыдущей команды
если предыдущая NULL, значит команда первая. Просматривает список редиректов,
активным будет последний редирект, останавливается на первом битом редиректе
редиректы в приорете над пайпом.
пайп создается, но в случае ошибки, как и в случае активного редиректа
тут же закрывается как входной из предыдущей команды, так и выходной текущей.
*/
int	setredir(t_prgexec *prevcmd, t_prgexec *cmd)
{
	int	err;

	if (cmd->is_pipe || (prevcmd && prevcmd->pipe))
		pipe(cmd->pipe);
	err = open_rdr(cmd);
	return (ERR_OK);
}

/*
обратная функция. разбирает пайп
*/
void	unsetredir(t_prgexec *prevcmd, t_prgexec *cmd)
{
	(void)prevcmd;
	if (cmd->is_pipe)
		return ;
}
