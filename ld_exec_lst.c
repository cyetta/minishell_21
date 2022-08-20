/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_exec_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 23:42:46 by cyetta            #+#    #+#             */
/*   Updated: 2022/08/20 14:39:54 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "ft_error.h"
#include <sys/stat.h>
#include <fcntl.h>

/*
clean enviroment variable array
*/
void	a_env_free(t_mshell *data)
{
	int	i;

	if (data->a_env)
	{
		i = 0;
		while (data->a_env[i])
			free(data->a_env[i++]);
		free(data->a_env);
		data->a_env = NULL;
	}
}

/*
load in enviroment variable array an actuals values for execution command
*/
int	a_env_init(t_mshell *data)
{
	int		qnt;
	int		j;
	t_list	*i;

	a_env_free(data);
	qnt = ft_lstsize(data->env_lst);
	data->a_env = malloc(sizeof(char *) * (++qnt));
	if (!data->a_env)
		exit(ft_error(ERR_MALLOC));
	j = 0;
	i = data->env_lst;
	while (i)
	{
		data->a_env[j++] = ktable2str((t_ktable *)i->content);
		i = i->next;
	}
	data->a_env[j] = NULL;
	return (ERR_OK);
}

/*
Clear exec element, callback function for ft_lstclear
*/
void	exc_elmt_del(void *elm)
{
	t_prgexec	*i;

	i = (t_prgexec *)elm;
	free(i->argv);
	if (i->f_stdin != 0)
		close(i->f_stdin);
	if (i->f_stout != 1)
		close(i->f_stout);
	free(i);
}

int	count_tkn_str(t_list *t)
{
	int		cnt;

	cnt = 0;
	while (t && ((t_token *)t->content)->e_lxm != PIPE)
	{
		if (((t_token *)t->content)->e_lxm != STRINGLN)
			cnt++;
		else if (((t_token *)(t)->content)->e_lxm >= PIPE && \
	((t_token *)(t)->content)->e_lxm <= HERE_DOC)
			t = t->next;
		t = t->next;
	}
}

/*
Open\close redirection files for exec element.
return ERR_OK if no error open files
 */
int	open_rdr(t_list **t, t_prgexec *p, t_mshell *data)
{
	*t = (*t)->next;
	return (ERR_OK);
}

t_prgexec	*crt_exc_elmt(t_list *t)
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
	ret->mdata = data;
	ret->f_stdin = 0;
	ret->f_stout = 1;
	return (ret);
}

/*
Create new exec element from token list, open\close files for redirection
return err or ERR_OK
 */
int	new_exc_elmt(t_prgexec	**ret, t_list **t, t_mshell *data)
{
	int			cnt;
	int			i;
	int			err;

	err = ERR_OK;
	cnt = 0;
	while (*t && ((t_token *)(*t)->content)->e_lxm != PIPE)
	{
		if (((t_token *)(*t)->content)->e_lxm != STRINGLN)
			(*ret)->argv[cnt++] = ((t_token *)(*t)->content)->value;
		else if (((t_token *)(*t)->content)->e_lxm >= PIPE && \
	((t_token *)(*t)->content)->e_lxm <= HERE_DOC)
			err = open_rdr(t, ret, data);
		if (err)
			return (err);
		*t = (*t)->next;
	}
	return (err);
}

/*
Create command list for execution
return error or ERR_OK
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
		if (!err)
			break ;
		lst_i = ft_lstnew(exec_i);
		if (!lst_i)
			exit(ft_error(ERR_MALLOC));
		ft_lstadd_back(&data->exec_lst, lst_i);
		t = t->next;
	}
	if (err == ERR_OK)
		return (err);
	ft_lstclear(&data->exec_lst, exc_elmt_del);
	if (exec_i)
		exc_elmt_del((void *) exec_i);
	return (err);
}
/* 	int	i = -1;
	while ((data->a_env)[++i])
		printf("a_env: %s\n", data->a_env[i]);
 */