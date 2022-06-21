/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:50:30 by cyetta            #+#    #+#             */
/*   Updated: 2022/06/21 15:28:55 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "ft_error.h"
#include "minishell.h"
#include "lexer.h"

void	print(void)
{
}

int	parse_cmd(t_mshell *data, char *cmd)
{
	int		err;

	err = lexer(&data->tkn_lst, cmd);
	if (err)
		return (is_syntax_err(ft_error(err)));
	ft_lstiter(data->tkn_lst, prn_tkn_elmnt);
	ft_lstclear(&data->tkn_lst, del_tkn_elmnt);
	return (0);
}

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

/* 	t_list		*lst;
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
int	init_data(t_mshell *shell_prm, char **argp)
{
	if (ld_env2lst(&shell_prm->env, argp))
		return (ERR_INIT_4);
	shell_prm->tkn_lst = NULL;
	return (0);
}

	// (void) argc;
	// (void) argv;
	// (void) argp;
int	main(int argc, char **argv, char **argp)
{
	t_mshell	shell_prm;
	char	*s;
	int		err;

	pr_argvp(argc, argv, argp); // test print argv, argp
	if (argc > 1)
		return (ft_error(ERR_USAGE));
	else if (init_data(&shell_prm, argp))
		return (ft_error(ERR_INIT_4));
	ft_lstiter(shell_prm.env, ktblitm_prn); // test print env variable list
	while (1)
	{
		s = readline("minishell$ ");
		if (!s)
			break ;
		else if (*s)
			add_history(s);
		printf("%s\n", s);
		err = parse_cmd(&shell_prm, s);
		free(s);
		if (err != ERR_SYNTAX && err != ERR_OK)
			break ;
	}
	rl_clear_history();
	ft_lstclear(&shell_prm.env, ktblitm_del);
	return (0);
}
