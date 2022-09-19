/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:41:09 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/19 09:49:44 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"
# include <stdio.h>
# include <unistd.h>

int		is_builtin(t_prgexec *cmd);
int		builtin_echo(t_prgexec *cmd);
int		builtin_cd(t_prgexec *cmd);
int		builtin_pwd(t_prgexec *cmd);
int		builtin_export(t_prgexec *cmd);
int		builtin_unset(t_prgexec *cmd);
int		builtin_env(t_prgexec *cmd);
int		builtin_exit(t_prgexec *cmd);
#endif
