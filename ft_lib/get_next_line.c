/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 00:14:13 by cyetta            #+#    #+#             */
/*   Updated: 2022/02/26 15:14:03 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "get_next_line.h"

/*
FindFileDescriptor fd in the list *fdlisthead.
Returns NULL, if it doesn't exist.
*/
t_fdesc	*findfdesc(t_fdesc *fdlsthead, int fd)
{
	while (fdlsthead)
	{
		if (fdlsthead->fd == fd)
			break ;
		fdlsthead = fdlsthead->next;
	}
	return (fdlsthead);
}

/*
Returns the pointer to actual file descriptor t_fdesc from list *fdlsthd.
If it doesn't exist, creates, initializes and appends it to front in the list.
If an error occurred during creation, returns NULL, fdlsthd doesn't changes.
*/
static t_fdesc	*createfdesc(t_fdesc **fdlsthd, int fd)
{
	t_fdesc	*fdesc;

	if (fd < 0)
		return (NULL);
	fdesc = findfdesc(*fdlsthd, fd);
	if (fdesc)
		return (fdesc);
	fdesc = (t_fdesc *)malloc(sizeof(t_fdesc));
	if (!(fdesc))
		return (NULL);
	fdesc->buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (!fdesc->buf)
	{
		free(fdesc);
		return (NULL);
	}
	fdesc->fd = fd;
	fdesc->cnt = 0;
	fdesc->next = *fdlsthd;
	*fdlsthd = fdesc;
	return (fdesc);
}

static void	freefdesc(t_fdesc **fdlsthd, int fd)
{
	t_fdesc	*prev;
	t_fdesc	*curr;
	t_fdesc	*next;

	curr = *fdlsthd;
	while (curr)
	{
		next = curr->next;
		if (curr->fd == fd)
		{
			if (curr == *fdlsthd)
				*fdlsthd = next;
			else
				prev->next = next;
			free(curr->buf);
			free(curr);
		}
		else
			prev = curr;
		curr = next;
	}
}

/*
Creates new string from str & fd->buf, like str_join
fdbuf_cnt - quantity char to copy from fd->buf, != 0
*str_len - curent size of str,
returns NULL on allocation error
the previose *str is released.
*/
static char	*addbuff2str(char *str, size_t *str_len, t_fdesc *fd)
{
	char	*newstr;
	int		fdbuf_cnt;

	fdbuf_cnt = 0;
	while (fdbuf_cnt < fd->cnt && fd->buf[fdbuf_cnt] != '\n')
		++fdbuf_cnt;
	if (fdbuf_cnt < fd->cnt)
		++fdbuf_cnt;
	newstr = (char *)malloc(*str_len + fdbuf_cnt + 1);
	if (newstr)
	{
		if (*str_len)
			ft_memcpy(newstr, str, *str_len);
		ft_memcpy(newstr + *str_len, fd->buf, fdbuf_cnt);
		newstr[*str_len + fdbuf_cnt] = '\0';
		if (fd->cnt - fdbuf_cnt)
			ft_memcpy(fd->buf, fd->buf + fdbuf_cnt, fd->cnt - fdbuf_cnt);
		fd->cnt -= fdbuf_cnt;
		*str_len += fdbuf_cnt;
	}
	if (str)
		free(str);
	return (newstr);
}

/*
returns a pointer to the next line from fd
allocates a char("\n") string in memory and returns a pointer to it
if NULL - allocation error or error reading or stream is empty
*/
char	*get_next_line(int fd)
{
	static t_fdesc	*fdesclst = NULL;
	t_fdesc			*fdesc;
	char			*nextl;
	size_t			nextl_len;

	fdesc = createfdesc(&fdesclst, fd);
	if (fd < 0 || BUFFER_SIZE <= 0 || !fdesc)
		return (NULL);
	if (!fdesc->cnt)
		fdesc->cnt = read(fdesc->fd, fdesc->buf, BUFFER_SIZE);
	nextl = NULL;
	nextl_len = 0;
	while (fdesc->cnt > 0)
	{
		nextl = addbuff2str(nextl, &nextl_len, fdesc);
		if (!nextl || nextl[nextl_len - 1] == '\n')
			break ;
		fdesc->cnt = read(fdesc->fd, fdesc->buf, BUFFER_SIZE);
	}
	if (!nextl || (fdesc->cnt <= 0 && nextl[nextl_len - 1] != '\n'))
		freefdesc(&fdesclst, fd);
	return (nextl);
}
