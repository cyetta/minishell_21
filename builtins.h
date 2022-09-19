/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:41:09 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/19 09:24:55 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"
# include <stdio.h>
# include <unistd.h>

int		is_builtin(t_prgexec *cmd);
void	builtin_echo(t_prgexec *cmd);
int		buitin_cd(t_prgexec *cmd);
void	builtin_pwd(void);
int		buitin_export(t_prgexec *cmd);
int		buitin_unset(t_prgexec *cmd);
int		builtin_env(t_prgexec *cmd);
void	builtin_exit(t_prgexec *cmd);
#endif
