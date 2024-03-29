/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:21:09 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/30 16:28:26 by cyetta           ###   ########.fr       */
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

static int	b_export_prn(t_list *env_lst)
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
return TRUE if all ok, otherwie FAlSE and errormsg
*/
static int	is_env_acceptable(char *s)
{
	int	i;

	if (*s != '_' && !ft_isalpha(*s))
		return (err_prnt3n("minishell: export", s, \
	"is an invalid identifier", 0));
	i = 0;
	while (s[++i])
	{
		if (s[i] == '+' && s[i + 1] == '\0')
			return (err_prnt3n("minishell: export", s, \
		"is an invalid identifier", 0));
		else if (s[i] == '+' && s[i + 1] == '=')
			break ;
		else if (s[i] == '=')
			break ;
		else if (s[i] != '_' && !ft_isalnum(s[i]))
			return (err_prnt3n("minishell: export", s, \
		"is an invalid identifier", 0));
	}
	return (1);
}

static int	env_attach(t_list **env_lst, char *str)
{
	char		*ts;
	t_ktable	*tk_new;
	t_ktable	*tk_exist;

	tk_new = parse_envstr(str);
	if (!tk_new)
		return (err_prnt3n("minishell: export", str, \
		"not added, something went wrong", ERR_INIT_4));
	tk_new->key[ft_strlen(tk_new->key) - 1] = '\0';
	tk_exist = search_env_var(*env_lst, tk_new->key);
	if (tk_exist)
	{
		ts = ft_strjoin(tk_exist->value, tk_new->value);
		free(tk_exist->value);
		tk_exist->value = ts;
		ktblitm_del(tk_new);
	}
	else
		ft_lstadd_back(env_lst, ft_lstnew(tk_new));
	return (ERR_OK);
}

static int	env_add(t_list **env_lst, char *str)
{
	char		*ts;
	t_ktable	*tk_new;
	t_ktable	*tk_exist;

	tk_new = parse_envstr(str);
	if (!tk_new)
		return (err_prnt3n("minishell: export", str, \
		"not added, something went wrong", ERR_INIT_4));
	tk_exist = search_env_var(*env_lst, tk_new->key);
	if (!tk_exist)
		ft_lstadd_back(env_lst, ft_lstnew(tk_new));
	else if (tk_new->value)
	{
		ts = tk_exist->value;
		tk_exist->value = tk_new->value;
		tk_new->value = ts;
		ktblitm_del(tk_new);
	}
	else
		ktblitm_del(tk_new);
	return (ERR_OK);
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
	int		i;

	if (!cmd->argv[1])
		return (b_export_prn(cmd->mdata->env_lst));
	i = 0;
	while (cmd->argv[++i])
	{
		if (!is_env_acceptable(cmd->argv[i]))
			continue ;
		else if (ft_strnstr(cmd->argv[i], "+=", ft_strlen(cmd->argv[i])))
			env_attach(&cmd->mdata->env_lst, cmd->argv[i]);
		else
			env_add(&cmd->mdata->env_lst, cmd->argv[i]);
	}
	return (0);
}
