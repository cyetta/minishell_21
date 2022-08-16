/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:41:22 by cyetta            #+#    #+#             */
/*   Updated: 2022/08/16 23:37:57 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "ft_lib/libft.h"

/*
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
*/

typedef struct s_prgexec
{
	char	**argv;
	char	**envp;
	int		f_stdin;
	int		f_stout;
}	t_prgexec;

typedef struct s_ktable
{
	char			*key;
	char			*value;
}	t_ktable;

/*
Основная структура минишелл
	*env		-операционный список переменных среды, загружается при запуске
	*tkn_lst	-список токенов при раборе команды
	*exec_lst	-список запускаемых команд
	**a_env		-массив переменных среды, инициализируется при создании списка
запускаемых команд. ссылка на этот массив в каждой команде.
конец массива строка из \0
	errlvl		-errorlvl последней команды
	*msh_name	-хз, что это и зачем.
*/
typedef struct s_mshell
{
	t_list	*env;
	t_list	*tkn_lst;
	t_list	*exec_lst;
	char	**a_env;
	int		errlvl;
	char	*msh_name;
}	t_mshell;

t_ktable	*get_envitm(char *str);
void		ktblitm_del(void *elm);
void		ktblitm_prn(void *elm);
int			ld_env2lst(t_list **lst, char **argp);
#endif
