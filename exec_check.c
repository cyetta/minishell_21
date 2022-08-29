/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 20:10:42 by cyetta            #+#    #+#             */
/*   Updated: 2022/08/29 21:14:41 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <pthread.h>
#include "ft_util.h"
#include "minishell.h"
#include "executor.h"
#include "builtins.h"

/*
check for exist command in content
return 0 if command exit
return 1 if command not exist
*/
int	checkpath(void *key, void *content)
{
	t_mshell	*data;
	t_prgexec	*cmd;

	data = (t_mshell *)key;
	cmd = (t_prgexec *)content;
	if (is_builtin(cmd->argv[0]))
		return (0);
	return (1);
}

int	exec_checkcmd(t_mshell *data)
{
	t_prgexec	*err_cmd;

	err_cmd = ft_lstsearch(data->exec_lst, data, checkpath);
}
