/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:41:09 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/16 03:32:14 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# define BLT_ECHO 1
# define BLT_CD 2
# define BLT_PWD 3
# define BLT_EXPORT 4
# define BLT_UNSET 5
# define BLT_ENV 6
# define BLT_EXIT 7
# include "minishell.h"

int	is_builtin(t_prgexec *cmd);
int	builtin_echo(t_prgexec *cmd);
int	builtin_cd(t_prgexec *cmd);
int	builtin_pwd(t_prgexec *cmd);
int	builtin_export(t_prgexec *cmd);
int	builtin_unset(t_prgexec *cmd);
int	builtin_env(t_prgexec *cmd);
int	builtin_exit(t_prgexec *cmd);
#endif
