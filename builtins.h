/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:41:09 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/18 21:17:53 by macbook          ###   ########.fr       */
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
