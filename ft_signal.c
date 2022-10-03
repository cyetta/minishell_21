/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 09:05:13 by cyetta            #+#    #+#             */
/*   Updated: 2022/10/03 15:58:51 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>
#include "ft_util.h"
#include "ft_signal.h"

void	sig_hndlr(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \b\b\n", 5);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	sig_fork(int sig)
{
	if (sig == SIGINT)
		write(2, "\n", 1);
	if (sig == SIGQUIT)
		write(2, "Quit:\n", 6);
}

int	set_sigfork(char *cmd)
{
	char	*s;

	if (!cmd)
	{
		signal(SIGINT, sig_fork);
		signal(SIGQUIT, sig_fork);
	}
	else
	{
		s = ft_strrchr(cmd, '/');
		if ((s && !ft_strcmp(s, "/minishell")) || \
						(!s && !ft_strcmp(cmd, "minishell")))
			set_signal(FT_SIG_IGN);
		else
		{
			signal(SIGINT, sig_fork);
			signal(SIGQUIT, sig_fork);
		}
	}
	return (0);
}

/*
set signal handler
*/
int	set_signal(int type)
{
	if (type == FT_SIG_IGN)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (type == FT_SIG_DFL)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (type == FT_SIG_HDL)
	{
		signal(SIGINT, sig_hndlr);
		signal(SIGQUIT, SIG_IGN);
	}
	return (0);
}
