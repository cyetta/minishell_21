/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_lst_ld.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 23:42:46 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/14 00:57:58 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "lexer.h"
#include "parser.h"
#include "ft_error.h"

/*
count string for one execution element
*/
int	count_tkn_str(t_list *t)
{
	int		cnt;

	cnt = 0;
	while (t && ((t_token *)t->content)->e_lxm != PIPE)
	{
		if (((t_token *)t->content)->e_lxm == STRINGLN)
			cnt++;
		else if (((t_token *)(t)->content)->e_lxm >= PIPE && \
	((t_token *)(t)->content)->e_lxm <= HERE_DOC)
			t = t->next;
		t = t->next;
	}
	return (cnt);
}

/*
create and init new execution element
*/
static t_prgexec	*crt_exc_elmt(t_list *t, t_mshell *data)
{
	int			cnt;
	int			i;
	t_prgexec	*ret;

	ret = malloc(sizeof(t_prgexec));
	if (!ret)
		exit(ft_error(ERR_MALLOC));
	cnt = count_tkn_str(t);
	ret->argv = malloc(sizeof(char *) * (++cnt));
	if (!ret->argv)
		exit(ft_error(ERR_MALLOC));
	i = -1;
	while (++i < cnt)
		ret->argv[i] = NULL;
	ret->execmd = NULL;
	ret->rdr_lst = NULL;
	ret->mdata = data;
	ret->f_stdin = 0;
	ret->f_stout = 1;
	ret->is_pipe = 0;
	data->hdoc_isnewcmd = 1;
	return (ret);
}

/*
Creates new exec element by token list from current position, open\close files \
for redirection, change position in list for create next exec element.
returns ERR_OK or ERR_ on error
*/
int	new_exc_elmt(t_prgexec	**ret, t_list **t, t_mshell *data)
{
	int			cnt;
	int			err;

	(*ret) = crt_exc_elmt(*t, data);
	err = ERR_OK;
	cnt = 0;
	while (*t && ((t_token *)(*t)->content)->e_lxm != PIPE)
	{
		if (((t_token *)(*t)->content)->e_lxm == STRINGLN)
			(*ret)->argv[cnt++] = ((t_token *)(*t)->content)->value;
		else if (((t_token *)(*t)->content)->e_lxm >= PIPE && \
	((t_token *)(*t)->content)->e_lxm <= HERE_DOC)
			err = open_rdr(t, *ret, data);
		if (err)
			return (err);
		*t = (*t)->next;
	}
	if (*t && ((t_token *)(*t)->content)->e_lxm == PIPE)
		(*ret)->is_pipe = 1;
	return (err);
}

/*
Create command list for execution
returns ERR_OK or ERR_ on error
*/
int	ld_exec_lst(t_mshell *data)
{
	t_list		*t;
	t_list		*lst_i;
	t_prgexec	*exec_i;
	int			err;

	data->exec_lst = NULL;
	a_env_init(data);
	t = data->tkn_lst;
	while (t)
	{
		err = new_exc_elmt(&exec_i, &t, data);
		if (err)
			break ;
		lst_i = ft_lstnew(exec_i);
		if (!lst_i)
			exit(ft_error(ERR_MALLOC));
		ft_lstadd_back(&data->exec_lst, lst_i);
		if (t)
			t = t->next;
	}
	if (err == ERR_OK)
		return (err);
	ft_lstclear(&data->exec_lst, exc_elmt_del);
	exc_elmt_del((void *) exec_i);
	return (err);
}
/* 	int	i = -1;
	while ((data->a_env)[++i])
		printf("a_env: %s\n", data->a_env[i]);
 */