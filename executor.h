/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 20:17:44 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/01 16:42:54 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

int		exec_cmd(t_mshell *data);
int		exec_checkcmd(t_mshell *data);
char	*get_path(char **env);
int		is_cmd_exist(char *cmd);
char	*getexecpath(char *cmd, char **env);
char	*findexecbypath(char *cmd, char *vpath);
char	*findexecbypathret(int err, char *cmd, char *ret);
#endif