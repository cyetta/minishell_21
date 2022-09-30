/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_lst_ld_u.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 23:42:46 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/30 19:22:10 by cyetta           ###   ########.fr       */
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
		if (((t_ktable *)i->content)->value)
			data->a_env[j++] = ktable2str((t_ktable *)i->content);
		i = i->next;
	}
	data->a_env[j] = NULL;
	data->exec_lst = NULL;
	return (ERR_OK);
}

/*
Frees tokens content and itself
Callback function for ft_lstclear()
*/
void	exec_rdrle_del(void *elm)
{
	t_token	*tkn;

	tkn = (t_token *)elm;
	if (tkn->e_lxm == HERE_DOC && tkn->value)
	{
		if (access(tkn->value, F_OK) == 0)
			unlink(tkn->value);
		free(tkn->value);
	}
	free(tkn);
}

/*
Clear exec element, callback function for ft_lstclear
element *argv[] is pointer to string in tkn_lst thats will be cleared
by del_tkn_elmnt()
*/
void	exc_elmt_del(void *elm)
{
	t_prgexec	*cmd;

	cmd = (t_prgexec *)elm;
	if (cmd->f_stdin > 2)
		close(cmd->f_stdin);
	if (cmd->f_stout > 2)
		close(cmd->f_stout);
	if (cmd->execmd)
		free(cmd->execmd);
	free(cmd->argv);
	ft_lstclear(&cmd->rdr_lst, exec_rdrle_del);
	free(cmd);
}

/*
Print exec element, callback function for ft_lstiter
*/
void	exc_elmt_prn(void *elm)
{
	t_prgexec	*p;
	int			i;

	p = (t_prgexec *)elm;
	i = 0;
	printf("--- %s in exec %p ---\n", p->execmd, p);
	while (p->argv[i])
		printf("%s\n", p->argv[i++]);
	printf("--- redirect ---\n");
	ft_lstiter(p->rdr_lst, tkn_elmnt_prn);
	printf("--- redir ---\nstdin - %d\nstout - %d\npipe - %d\nenv - \
	%p\n\n", p->f_stdin, p->f_stout, p->is_pipe, p->mdata->a_env);
}
