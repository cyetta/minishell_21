/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:34:21 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/16 03:43:30 by cyetta           ###   ########.fr       */
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

	err = open_rdr(cmd);
	if (err)
		return (err);
	if (cmd->is_pipe || (prevcmd && prevcmd->pipe))
// here pipe
		return (ERR_OK);
	else
// here not a pipe
		return (ERR_OK);
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
