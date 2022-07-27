/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:41:22 by cyetta            #+#    #+#             */
/*   Updated: 2022/06/25 20:18:03 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "ft_lib/libft.h"

typedef struct s_prgexec
{
	char	*pathname;
	char	**argv;
	char	**envp;
}	t_prgexec;

typedef struct s_toexeclst{
	t_prgexec			*prgm;
	struct s_toexeclst	*next;
}	t_toexeclst;

typedef struct s_lst
{
	int				type;
	char			*value;
	char			**cmd;
	int				str_position;
	struct s_lst	*next;
}					t_lst;

typedef struct s_ktable
{
	char			*key;
	char			*value;
}	t_ktable;

typedef struct s_mshell
{
	t_list	*env;
	t_list	*tkn_lst;
	int		errlvl;
	char	*msh_name;
}	t_mshell;

t_ktable	*get_envitm(char *str);
void		ktblitm_del(void *elm);
void		ktblitm_prn(void *elm);
int			ld_env2lst(t_list **lst, char **argp);
#endif
