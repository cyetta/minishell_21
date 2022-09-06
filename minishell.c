/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:50:30 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/06 18:14:09 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "ft_error.h"
#include "minishell.h"
#include "lexer.h"
#include "parser.h"
#include "executor.h"

int	parse_cmd(t_mshell *data, char *cmd)
{
	int	err;

	if (!*cmd)
		return (ERR_EMPTYCMD);
	err = lexer(&data->tkn_lst, cmd);
	if (err)
		return (is_syntax_err(ft_error(err)));
	if (((t_token *)data->tkn_lst->content)->e_lxm == SPACESTR)
		ft_lstdelnode(&data->tkn_lst, data->tkn_lst, tkn_elmnt_del);
	else
		add_history(cmd);
ft_lstiter(data->tkn_lst, tkn_elmnt_prn);
printf("----\n");
	if (ft_lstsize(data->tkn_lst) == 0)
		return (ERR_EMPTYCMD);
	err = tknlst_expander(data);
ft_lstiter(data->tkn_lst, tkn_elmnt_prn);
printf("\n");
	if (err)
		return (is_syntax_err(ft_error(err)));
	err = ld_exec_lst(data);
ft_lstiter(data->exec_lst, exc_elmt_prn);
	if (err)
		return (is_syntax_err(ft_error(err)));
	return (ERR_OK);
}

int	exec_cmd(t_mshell *data)
{
	int	err;

	err = exec_checkcmd(data);
	if (err)
		return (is_syntax_err(ft_error(err)));
ft_lstiter(data->exec_lst, exc_elmt_prn);
printf("----\n");
	return (ERR_OK);
}

/*
Initialize main data structure,
load enviroment variable in list
*/
int	init_data(t_mshell *shell_prm, char **argp)
{
	shell_prm->env_lst = NULL;
	if (ld_env2lst(&shell_prm->env_lst, argp))
		return (ERR_INIT_4);
	shell_prm->tkn_lst = NULL;
	shell_prm->errlvl = 0;
	shell_prm->a_env = NULL;
	shell_prm->hdoc_cnt = 0;
	shell_prm->exec_lst = NULL;
	return (0);
}

void	clear_data(t_mshell *shell_prm)
{
	ft_lstclear(&shell_prm->exec_lst, exc_elmt_del);
	ft_lstclear(&shell_prm->tkn_lst, tkn_elmnt_del);
	a_env_free(shell_prm);
	unlink_hdoc(shell_prm);
}

int	main(int argc, char **argv, char **argp)
{
	t_mshell	shell_prm;
	char		*s;
	int			err;

	(void) argv;
	if (argc > 1)
		return (ft_error(ERR_USAGE));
	else if (init_data(&shell_prm, argp))
		return (ft_error(ERR_INIT_4));
ft_lstiter(shell_prm.env_lst, ktblitm_prn); // test print env variable list
	while (1)
	{
		s = readline("minishell$ ");
		if (!s)
			break ;
		err = parse_cmd(&shell_prm, s);
		free(s);
		if (err != ERR_OK && err != ERR_SYNTAX && err != ERR_EMPTYCMD)
			break ;
		else if (err == ERR_OK)
			err = exec_cmd(&shell_prm);
		clear_data(&shell_prm);
	}
	clear_data(&shell_prm);
	ft_lstclear(&shell_prm.env_lst, ktblitm_del);
	rl_clear_history();
	return (0);
}

/*
void	pr_argvp(int argc, char **argv, char **argp)
{
	int		i;

	i = -1;
	while (argv[++i])
		printf("%d [%d]%s\n", argc, i, argv[i]);
	i = -1;
	while (argp[++i])
		printf("%s\n", argp[i]);
}

 	t_list		*lst;
	t_ktable	*itm;
	int			i;

	i = -1;
	lst = NULL;
	while (argp[++i])
	{
		itm = get_envitm(argp[i]);
		lst = ft_lstnew(itm);
		ft_lstadd_back(shell_p
rm->env, lst);
	} */
