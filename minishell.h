/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:41:22 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/01 23:31:30 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "ft_lib/libft.h"
# include <pthread.h>
# include <stdio.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>

typedef struct s_ktable
{
	char			*key;
	char			*value;
}	t_ktable;

/*
Основная структура минишелл:
	*env_lst	- операционный список переменных среды, загружается при запуске
	*tkn_lst	- список токенов при раборе команды
	*exec_lst	- список запускаемых команд
	**a_env		- массив переменных среды, инициализируется при создании списка
запускаемых команд. ссылка на этот массив в каждой команде s_prgexec через mdata
конец массива строка из \0
	errlvl		- errorlvl последней команды
	hdoc_cnt	- счетчик heredoc
	hdoc_isnewcmd	- флаг новой команды, нужен для инкримента сетчика временных 
файлов heredoc
	*msh_name	- хз, что это и зачем.
*/
typedef struct s_mshell
{
	t_list	*env_lst;
	t_list	*tkn_lst;
	t_list	*exec_lst;
	char	**a_env;
	int		errlvl;
	int		hdoc_cnt;
	int		hdoc_isnewcmd;
	char	*msh_name;
}	t_mshell;

typedef struct s_prgexec
{
	char		**argv;
	t_mshell	*mdata;
	int			f_stdin;
	int			f_stout;
	pid_t		cmd_pid;
	int			pipe;
}	t_prgexec;

t_ktable	*get_envitm(char *str);
char		*ktable2str(t_ktable *itm);
void		ktblitm_del(void *elm);
void		ktblitm_prn(void *elm);
int			ld_env2lst(t_list **lst, char **argp);
#endif
