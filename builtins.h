/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:41:09 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/30 16:28:25 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"

int			is_builtin(t_prgexec *cmd);
int			runbuiltin(t_prgexec *cmd, int bnum);
int			builtin_echo(t_prgexec *cmd);
int			builtin_cd(t_prgexec *cmd);
int			builtin_pwd(t_prgexec *cmd);
int			builtin_export(t_prgexec *cmd);
int			builtin_unset(t_prgexec *cmd);
int			builtin_env(t_prgexec *cmd);
int			builtin_exit(t_prgexec *cmd);
char		*get_env_var(t_prgexec *cmd, char *var);
t_ktable	*search_env_var(t_list *envlst, char *var);
int			add_env_var(t_list **envlst, char *var, char *value);
int			replace_env_var(t_list **envlst, char *var, char *value);
int			del_env_var(t_list **envlst, char *var);
int			check_option(char *argv);
int			throw_error_usage(char *cmd, char *argv);
int			throw_error_env(char *cmd, char *argv);
int			valid_env_name(char *identifier);
int			ktblitm_low(void *key, void *content);
void		b_export_delsorted(void *content);
void		b_export_print(void *content);
#endif
