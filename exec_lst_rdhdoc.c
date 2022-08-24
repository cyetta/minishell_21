/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_lst_rdhdoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 15:31:49 by cyetta            #+#    #+#             */
/*   Updated: 2022/08/24 21:59:41 by cyetta           ###   ########.fr       */
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

int	create_hdocfname(char **path, t_mshell *data)
{
	const char	*tmp[] = {"TMP", "TEMP", "TMPDIR"};
	int			i;
	int			fd;

	i = 3;
	while (--i >= 0)
	{
		*path = get_tmpfname(tmp[i], data);
		if (**path == 0)
			continue ;
		fd = open(*path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
		if (fd > 2)
			return (fd);
		free(*path);
	}
	*path = append_tmpfname("", data);
	fd = open(*path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd < 0)
		err_prnt3n("minishell", *path, strerror(errno), ERR_SYNTAX_ERRNO);
	return (fd);
}

int	write_hdoc(int fd, char *hdoc)
{
	char	*s;
	int		cnt;

	s = readline(">");
	while (s && !ft_strcmp(s, hdoc))
	{
		cnt = write(fd, s, ft_strlen(s));
		if (cnt == -1)
			return (err_prnt3n("minishell", "", strerror(errno), ERR_SYNTAX_ERRNO));
		free(s);
		s = readline(">");
	}
	return (ERR_OK);
}

int	f_rdrhere(t_list **t, t_prgexec *p, t_mshell *data)
{
	char	*hdoc;
	char	*hdocfname;
	int		err;

	data->hdoc_cnt++;
	hdoc = ((t_token *)(*t)->next->content)->value;
	p->f_stdin = create_hdocfname(&hdocfname, data);
	if (p->f_stdin < 0)
		return (ERR_SYNTAX_ERRNO);
	err = write_hdoc(p->f_stdin, hdoc);
	if (!err)
		return (ERR_SYNTAX_ERRNO);
	close(p->f_stdin);
	p->f_stdin = open(hdocfname, O_RDONLY);
	if (p->f_stdin == -1)
		return (err_prnt3n("minishell", ((t_token *) \
	(*t)->next->content)->value, strerror(errno), ERR_SYNTAX_ERRNO));
	*t = (*t)->next;
	return (ERR_OK);
}
