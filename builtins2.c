/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:21:09 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/30 03:53:21 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "ft_util.h"
#include "builtins.h"
#include "ft_error.h"
#include "parser.h"
#include "lexer.h"

int	ktblitm_low(void *key, void *content)
{
	t_ktable	*t_key;
	t_ktable	*t_content;

	t_key = (t_ktable *)key;
	t_content = (t_ktable *)content;
	if (ft_strcmp(t_key->key, t_content->key) >= 0)
		return (0);
	return (1);
}

void	b_export_delsorted(void *content)
{
	(void)content;
}

void	b_export_print(void *content)
{
	t_ktable	*t_content;

	t_content = (t_ktable *)content;
	if (t_content->value)
		printf("declare -x %s=%s\n", t_content->key, t_content->value);
	else
		printf("declare -x %s\n", t_content->key);
}

int	b_export_prn(t_list *env_lst)
{
	t_list	*sorted;
	t_list	*tl;
	t_list	*newlst;

	sorted = NULL;
	while (env_lst)
	{
		newlst = ft_lstnew(env_lst->content);
		if (!newlst)
			exit (ft_error(ERR_MALLOC));
		tl = ft_lstsearch(sorted, env_lst->content, ktblitm_low);
		if (!tl)
			ft_lstadd_back(&sorted, newlst);
		else
			ft_lstinsbeforenode(&sorted, tl, newlst);
		env_lst = env_lst->next;
	}
	ft_lstiter(sorted, b_export_print);
	ft_lstclear(&sorted, b_export_delsorted);
	return (ERR_OK);
}

/*
Checking the environment variable name for validity
stops at '=' and '+='
*/
int	is_env_acceptable(char *s)
{
	int	i;

	if (*s != '_' || !ft_isalpha(*s))
		return (0);
	i = 0;
	while (s[++i])
	{
		if (s[i] == '+' && s[i + 1] == '\0')
			return (0);
		else if (s[i] == '+' && s[i + 1] == '=')
			break ;
		else if (s[i] == '=')
			break ;
		else if (s[i] != '_' && !ft_isalnum(s[i]))
			return (0);
	}
	return (1);
}

/*
export with no options
set the export attribute for variables
export name[=word]...
The shell shall give the export attribute to the variables corresponding to the
specified names, which shall cause them to be in the environment of subsequently
executed commands. If the name of a variable is followed by = word, then the
value of that variable shall be set to word.
 */
int	builtin_export(t_prgexec *cmd)
{
	int	i;

	if (!cmd->argv[1])
		return (b_export_prn(cmd->mdata->env_lst));
	return (0);
	i = -1;
	while (cmd->argv[++i])
	{
		if (!is_env_acceptable(cmd->argv[++i]))

	}
}

/*
unset with no options
unset [-fv] name ...
unset values and attributes of variables and functions
Each variable or function specified by name shall be unset.
 */
int	builtin_unset(t_prgexec *cmd)
{
	int		i;

	i = 0;
	while (cmd->argv[++i])
		del_env_var(&cmd->mdata->env_lst, cmd->argv[i]);
	return (ERR_OK);
}

/*
env with no options or arguments
env [-iv] [-P altpath] [-S string] [-u name] [name=val ...] [utility [arg ...]]
The env utility executes another utility after modifying the environment as
specified on the command line.  Each name=value option specifies the setting
of an environment variable, name, with a value of value.  All such environment
variables are set before the utility is executed.
 */
int	builtin_env(t_prgexec *cmd)
{
	int	i;

	if (cmd->argv[1])
		return (err_prnt3n("minishell", "env", "too many arguments", 1));
	i = 0;
	while (cmd->mdata->a_env[++i])
		printf("%s\n", cmd->mdata->a_env[i]);
	return (0);
}

/*
 exit with no options
 */
int	builtin_exit(t_prgexec *cmd)
{
	int	i;

	if (cmd->argv[1] && cmd->argv[2])
		return (err_prnt3n("minishell", "exit", "too many arguments", 1));
	if (!cmd->argv[1])
		exit(err_prnt3n("exit\n", NULL, NULL, 0));
	i = 0;
	if (cmd->argv[1][0] == '-')
		i = 1;
	while (ft_isdigit(cmd->argv[1][i]))
		i++;
	if (cmd->argv[1][i] != '\0' || i > 18 || (cmd->argv[1][0] == '-' && i == 1))
		exit (err_prnt3n("minishell: exit", cmd->argv[1], \
	"numeric argument required", 255));
	exit(err_prnt3n("exit\n", NULL, NULL, ft_atoi(cmd->argv[1]) % 256));
}
