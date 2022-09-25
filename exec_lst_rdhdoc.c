/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_lst_rdhdoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 15:31:49 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/25 22:25:38 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "lexer.h"
#include "parser.h"
#include "ft_error.h"

/*
function to bypass the 25 line limit
*/
static char	*findtmpath(int *i, const char **tmp, t_mshell *data)
{
	char	*path;

	*i = 4;
	while (--(*i) >= 0)
	{
		path = get_tmpfname(tmp[*i], data);
		if (*path != '\0')
			break ;
		free(path);
	}
	return (path);
}

/*
creates temporary file fd for write heredoc in temporary directory $TMPDIR or \
in current directory, if $TMPDIR not find
returns:
fd - temporary file descriptor
path - temporary file path zstring(malloc), if fd is actual or NULL if fd = -1
*/
int	create_hdocfname(char **path, t_mshell *data)
{
	const char	*tmp[] = {"", "TMP", "HOME", "TMPDIR"};
	int			i;
	int			fd;

	*path = findtmpath(&i, tmp, data);
	while (access(*path, F_OK | W_OK) == 0)
	{
		data->hdoc_cnt++;
		free(*path);
		*path = get_tmpfname(tmp[i], data);
	}
	if (errno == ENOENT)
	{
		fd = open(*path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
		if (fd > 2)
			return (fd);
	}
	err_prnt3n("minishell", *path, strerror(errno), ERR_SYNTAX_ERRNO);
	free(*path);
	*path = NULL;
	return (-1);
}

/*
Write string to temporary file fd, stop by heredoc or ctrl+d
On ctrl+c the process must return to the mshell without executing
and the errorlevel should be set to 1
*/
int	write_hdoc(int fd, char *hdoc)
{
	char	*s;
	int		cnt;

	cnt = 0;
	s = readline("> ");
	while (s && ft_strcmp(s, hdoc))
	{
		cnt = write(fd, s, ft_strlen(s));
		if (cnt == -1)
			break ;
		cnt = write(fd, "\n", 1);
		if (cnt == -1)
			break ;
		free(s);
		s = readline("> ");
	}
	if (!s)
		return(ERR_CTRLD_QUIT);
	free(s);
	if (cnt == -1)
		return (err_prnt3n("minishell", "", strerror(errno), ERR_SYNTAX_ERRNO));
	return (ERR_OK);
}

/*
create heredoc redirection for execution element
надо переделать под список

int	f_rdrhdoc(t_list **t, t_prgexec *p, t_mshell *data)
{
	char	*hdocfname;
	int		err;
	int		fd;

	fd = create_hdocfname(&hdocfname, data);
	if (fd < 0)
		return (ERR_SYNTAX_ERRNO);
	err = write_hdoc(fd, ((t_token *)(*t)->next->content)->value);
	if (err)
		return (ERR_SYNTAX_ERRNO);
	close(fd);
	p->f_stdin = open(hdocfname, O_RDWR);
	if (p->f_stdin == -1)
		return (err_prnt3n("minishell", ((t_token *) \
	(*t)->next->content)->value, strerror(errno), ERR_SYNTAX_ERRNO));
	*t = (*t)->next;
	return (ERR_OK);
}
*/

/*
create heredoc redirection for execution element
*/
int	exec_hdoc_add(t_list **t, t_prgexec *p)
{
	char	*hdocfname;
	t_list	*rd_tkn_le;
	int		err;
	int		fd;

	fd = create_hdocfname(&hdocfname, p->mdata);
	if (fd < 0)
		return (ERR_SYNTAX_ERRNO);
	err = new_tkn_elmnt(&rd_tkn_le, HERE_DOC, hdocfname);
	if (err)
		exit(ft_error(ERR_MALLOC));
	ft_lstadd_back(&p->rdr_lst, rd_tkn_le);
	err = write_hdoc(fd, ((t_token *)(*t)->next->content)->value);
	if (err)
		return (err);
	close(fd);
	*t = (*t)->next;
	return (ERR_OK);
}
