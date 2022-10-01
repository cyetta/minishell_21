/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:50:30 by cyetta            #+#    #+#             */
/*   Updated: 2022/10/01 04:45:58 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "ft_error.h"
#include "minishell.h"
#include "lexer.h"
#include "parser.h"
#include "executor.h"
#include "builtins.h"
#include "ft_signal.h"

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
	if (ft_lstsize(data->tkn_lst) == 0)
		return (ERR_EMPTYCMD);
	err = tknlst_expander(data);
	if (err)
		return (is_syntax_err(ft_error(err)));
	err = ld_exec_lst(data);
	if (err)
		return (is_syntax_err(ft_error(err)));
	return (ERR_OK);
}

/*
Initialize main data structure,
load enviroment variable in list
*/
int	init_data(t_mshell *shell_prm, int argc, char **argp)
{
	char	*t_pwd;

	if (argc > 1)
		exit (ft_error(ERR_USAGE));
	shell_prm->env_lst = NULL;
	if (ld_env2lst(&shell_prm->env_lst, argp))
		exit (ERR_INIT_4);
	shell_prm->tkn_lst = NULL;
	shell_prm->errlvl = 0;
	shell_prm->a_env = NULL;
	shell_prm->hdoc_cnt = 0;
	shell_prm->exec_lst = NULL;
	t_pwd = getcwd(NULL, 0);
	replace_env_var(&shell_prm->env_lst, "PWD", t_pwd);
	free (t_pwd);
	replace_env_var(&shell_prm->env_lst, "OLDPWD", NULL);
	return (0);
}

void	clear_data(t_mshell *shell_prm)
{
	ft_lstclear(&shell_prm->exec_lst, exc_elmt_del);
	ft_lstclear(&shell_prm->tkn_lst, tkn_elmnt_del);
	a_env_free(shell_prm);
}

int	main(int argc, char **argv, char **argp)
{
	t_mshell	shell_prm;
	char		*s;
	int			err;

	(void) argv;
	init_data(&shell_prm, argc, argp);
	while (1)
	{
		set_signal(FT_SIG_HDL);
		s = readline("minishell$ ");
		if (!s)
			break ;
		err = parse_cmd(&shell_prm, s);
		free(s);
		if (err != ERR_OK && err != ERR_SYNTAX && err != ERR_EMPTYCMD)
			break ;
		else if (err == ERR_OK)
			exec_start(&shell_prm);
		clear_data(&shell_prm);
	}
	clear_data(&shell_prm);
	ft_lstclear(&shell_prm.env_lst, ktblitm_del);
	rl_clear_history();
	return (0);
}
