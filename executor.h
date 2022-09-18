/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 20:17:44 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/18 16:49:43 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "builtins.h"

int		exec_cmd(t_mshell *data);
int		exec_checkcmd(t_mshell *data);
char	*get_path(char **env);
int		is_cmd_exist(char *cmd);
char	*getexecpath(char *cmd, char **env);
char	*findexecbypath(char *cmd, char *vpath);
int		exec_start(t_mshell *data);
int		setredir(t_prgexec *prevcmd, t_prgexec *cmd);
void	unsetredir(t_prgexec *prevcmd, t_prgexec *cmd);
int		open_rdr(t_prgexec *cmd);
int		f_rdrin(char *fname, t_prgexec *p);
int		f_rdrout(char *fname, t_prgexec *p);
int		f_rdr2out(char *fname, t_prgexec *p);

#endif