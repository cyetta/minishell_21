/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 20:10:42 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/09 20:05:42 by cyetta           ###   ########.fr       */
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

int	exec_start(t_mshell *data)
{
	t_list	*cmd;
	t_list	*prevcmd;

	cmd = data->exec_lst;
	prevcmd = NULL;
	while (cmd)
	{
		if (((t_prgexec *)cmd->content)->is_pipe)
			setpipe(prevcmd->content, cmd->content);
// in progress
		prevcmd = cmd;
		cmd = cmd->next;
	}
}
