/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_lst_rdhdoc_u.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 15:31:49 by cyetta            #+#    #+#             */
/*   Updated: 2022/08/24 22:06:17 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"
#include "ft_error.h"

/*
append to temporary filename counter from data->hdoc_cnt
return(malloc) path to temporary file
*/
static char	*append_tmpfnamecnt(char *src_path, t_mshell *data)
{
	char	*cnt;
	char	*path;

	cnt = ft_itoa(data->hdoc_cnt);
	if (!cnt)
		exit(ft_error(ERR_MALLOC));
	path = ft_strjoin(src_path, cnt);
	free(cnt);
	if (!path)
		exit(ft_error(ERR_MALLOC));
	return (path);
}

/*
append to source path temporary filename
return(malloc) path to temporary file
*/
char	*append_tmpfname(char *src_path, t_mshell *data)
{
	char	*t;
	char	*path;

	if (!src_path || !*src_path)
		t = ft_strdup(".");
	else
		t = ft_strdup(src_path);
	if (!t)
		exit(ft_error(ERR_MALLOC));
	if (t[ft_strlen(t) - 1] == '/')
		path = ft_strjoin(t, "minishell_tmp");
	else
		path = ft_strjoin(t, "/minishell_tmp");
	free(t);
	if (!path)
		exit(ft_error(ERR_MALLOC));
	t = path;
	path = append_tmpfnamecnt(t, data);
	free (t);
	return (path);
}

/*
Creates (malloc) path to a temporary file by environment variable
returns path to tmp file or null string if TMP variable is not found
*/
char	*get_tmpfname(const char *tmpenv, t_mshell *data)
{
	char	*path;
	char	*t;

	path = get_envvalue(tmpenv, data->env_lst);
	if (!path)
		exit(ft_error(ERR_MALLOC));
	if (!*path)
		return (path);
	t = path;
	path = append_tmpfname(t, data);
	free (t);
	return (path);
}
