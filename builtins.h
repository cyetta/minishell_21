/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:41:09 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/09 18:48:54 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"
# define BLT_ECHO 1
# define BLT_CD 2
# define BLT_PWD 3
# define BLT_EXPORT 4
# define BLT_UNSET 5
# define BLT_ENV 6
# define BLT_EXIT 7

int		is_builtin(t_prgexec *cmd);
void	buitin_echo(void);
void	buitin_cd(void);
void	buitin_pwd(void);
void	buitin_export(void);
void	buitin_unset(void);
void	buitin_env(void);
void	buitin_exit(void);
#endif
