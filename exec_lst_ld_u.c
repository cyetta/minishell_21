/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_lst_ld_u.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 23:42:46 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/01 20:57:48 by cyetta           ###   ########.fr       */
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
		data->a_env[j++] = ktable2str((t_ktable *)i->content);
		i = i->next;
	}
	data->a_env[j] = NULL;
	return (ERR_OK);
}

/*
Clear exec element, callback function for ft_lstclear
element argv[] is pointer to string in tkn_lst thats will be cleared
by del_tkn_elmnt
*/
void	exc_elmt_del(void *elm)
{
	t_prgexec	*cmd;

	cmd = (t_prgexec *)elm;
	if (cmd->f_stdin > 0)
		close(cmd->f_stdin);
	if (cmd->f_stout > 1)
		close(cmd->f_stout);
	if (cmd->execmd)
		free(cmd->execmd);
	free(cmd->argv);
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
	printf("--- redir ---\nstdin - %d\nstout - %d\npipe - %d\nenv - \
	%p\n---\n", p->f_stdin, p->f_stout, p->pipe, p->mdata->a_env);
}
