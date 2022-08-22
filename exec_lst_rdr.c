/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_lst_rdr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 15:31:49 by cyetta            #+#    #+#             */
/*   Updated: 2022/08/22 02:58:10 by cyetta           ###   ########.fr       */
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
#include "parser.h"
#include "ft_error.h"

int	f_rdrin(t_list **t, t_prgexec *p, t_mshell *data)
{
	int	err;

	(void)data;
	err = access(((t_token *)(*t)->next->content)->value, R_OK);
	if (err)
		return (err_prnt3n("minishell", ((t_token *) \
	(*t)->next->content)->value, strerror(errno), ERR_SYNTAX_ERRNO));
	if (p->f_stdin > 2)
		close(p->f_stdin);
	p->f_stdin = open(((t_token *)(*t)->next->content)->value, O_RDONLY);
	if (p->f_stdin == -1)
		return (err_prnt3n("minishell", ((t_token *) \
	(*t)->next->content)->value, strerror(errno), ERR_SYNTAX_ERRNO));
	*t = (*t)->next;
	return (ERR_OK);
}

int	f_rdrout(t_list **t, t_prgexec *p, t_mshell *data)
{
	(void)data;
	if (p->f_stout > 2)
		close(p->f_stout);
	p->f_stout = open(((t_token *)(*t)->next->content)->value, O_WRONLY | \
	O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (p->f_stout == -1)
		return (err_prnt3n("minishell", ((t_token *) \
	(*t)->next->content)->value, strerror(errno), ERR_SYNTAX_ERRNO));
	*t = (*t)->next;
	return (ERR_OK);
}

int	f_rdr2out(t_list **t, t_prgexec *p, t_mshell *data)
{
	(void)data;
	if (p->f_stout > 2)
		close(p->f_stout);
	p->f_stout = open(((t_token *)(*t)->next->content)->value, O_WRONLY | \
	O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (p->f_stout == -1)
		return (err_prnt3n("minishell", ((t_token *) \
	(*t)->next->content)->value, strerror(errno), ERR_SYNTAX_ERRNO));
	*t = (*t)->next;
	return (ERR_OK);
}

int	f_rdrhere(t_list **t, t_prgexec *p, t_mshell *data)
{
	(void)p;
	(void)data;
	*t = (*t)->next;
	return (ERR_OK);
}

typedef int	(*t_rdr_func)(t_list **t, t_prgexec *p, t_mshell *data);

/*
Open\close redirection files for exec element.
return ERR_OK if no error open files
 */
int	open_rdr(t_list **t, t_prgexec *p, t_mshell *data)
{
	int					err;
	const t_rdr_func	a_tkn_f[] = {f_rdrin, f_rdrout, f_rdr2out, f_rdrhere};

	if (!(*t)->next || ((t_token *)(*t)->next->content)->e_lxm != STRINGLN)
		return (ERR_NOFILESFOUND);
	err = a_tkn_f[((t_token *)(*t)->content)->e_lxm - REDIR_IN](t, p, data);
	return (err);
}
