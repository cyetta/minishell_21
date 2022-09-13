/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 20:17:44 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/14 01:37:20 by cyetta           ###   ########.fr       */
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
char	*findexecbypathret(int err, char *cmd, char *ret);
int		exec_start(t_mshell *data);
int		setredir(t_prgexec *prevcmd, t_prgexec *cmd);
void	unsetredir(t_prgexec *prevcmd, t_prgexec *cmd);
#endif