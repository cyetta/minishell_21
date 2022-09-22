/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_opn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 15:31:49 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/22 20:40:35 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "ft_error.h"
#include "executor.h"

int	f_rdrin(char *fname, t_prgexec *p)
{
	if (p->f_stdin > 2)
		close(p->f_stdin);
	p->f_stdin = open(fname, O_RDONLY);
	if (p->f_stdin == -1)
		return (err_prnt3n("minishell", fname, strerror(errno), \
	ERR_SYNTAX_ERRNO));
	return (ERR_OK);
}

int	f_rdrout(char *fname, t_prgexec *p)
{
	if (p->f_stout > 2)
		close(p->f_stout);
	p->f_stout = open(fname, O_WRONLY | O_CREAT | O_TRUNC, \
							S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (p->f_stout == -1)
		return (err_prnt3n("minishell", fname, strerror(errno), \
	ERR_SYNTAX_ERRNO));
	return (ERR_OK);
}

int	f_rdr2out(char *fname, t_prgexec *p)
{
	if (p->f_stout > 2)
		close(p->f_stout);
	p->f_stout = open(fname, O_WRONLY | O_CREAT | O_APPEND, \
							S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (p->f_stout == -1)
		return (err_prnt3n("minishell", fname, strerror(errno), \
	ERR_SYNTAX_ERRNO));
	return (ERR_OK);
}

typedef int	(*t_rdr_func)(char *fname, t_prgexec *p);

/*
Open\close redirection files for exec element.
return ERR_OK if no error open files or ERR_SYNTAX_ERRNO
 */
int	open_rdr(t_prgexec *cmd)
{
	int					err;
	const t_rdr_func	a_tkn_f[] = {f_rdrin, f_rdrout, f_rdr2out, f_rdrin};
	t_list				*t;

	t = cmd->rdr_lst;
	err = 0;
	while (t && !err)
	{
		err = a_tkn_f[((t_token *)(t)->content)->e_lxm - REDIR_IN] \
			(((t_token *)(t)->content)->value, cmd);
		t = t->next;
	}
	return (err);
}
