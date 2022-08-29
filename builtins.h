/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:41:09 by cyetta            #+#    #+#             */
/*   Updated: 2022/08/29 21:09:42 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int		is_builtin(char *cmd);
void	buitin_echo(void);
void	buitin_cd(void);
void	buitin_pwd(void);
void	buitin_export(void);
void	buitin_unset(void);
void	buitin_env(void);
void	buitin_exit(void);
#endif
