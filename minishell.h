/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:41:22 by cyetta            #+#    #+#             */
/*   Updated: 2022/10/03 02:38:11 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/types.h>
# include <unistd.h>
# include "ft_lib/libft.h"

/*
Структура для хранения списка переменных окружения
*/
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

/*
execmd	- команда с относительным или абсолютным путем запуска для execve
argv	- массив параметров запуска для argve, строки хранятся tkn_lst,
в массиве указатели на эти строки, очищать только массив, строки не нужно.
mdata	- указатель к основной структуре данных,там лежит массив переменных
окружения mdata->a_env
f_stdin	- дескриптор ввода  редиректа, приоритет над пайпом
f_stout	- дескриптор вывода редиректа, приоритет над пайпом
redirect - список структур t_token c именами файлов редиректов
cmd_pid	- PID запускаемого процесса
pipe	- признак вывода в пайп, ввод из пайпа смотри признак в предыдущей
команде
*/
typedef struct s_prgexec
{
	char		*execmd;
	char		**argv;
	t_mshell	*mdata;
	int			f_stdin;
	int			f_stout;
	t_list		*rdr_lst;
	pid_t		cmd_pid;
	int			is_pipe;
	int			pipe[2];
}	t_prgexec;

t_ktable	*parse_envstr(char *str);
char		*ktable2str(t_ktable *itm);
void		ktblitm_del(void *elm);
void		ktblitm_prn(void *elm);
int			ld_env2lst(t_list **lst, char **argp);
int			exit_clear(t_mshell *data, int errlvl);
#endif
