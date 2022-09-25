/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 09:05:13 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/25 22:24:07 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>

void	sig_hndlr(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \b\b\n", 5);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/*
set handler for SIGINT to sig_hndlr(), SIGQUIT to SIG_IGN (ignore)
*/
int	set_sighndlr(void)
{
	signal(SIGINT, sig_hndlr);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}

/*
set signal handler to default ignore
SIGINT to SIG_IGN, SIGQUIT to SIG_IGN
*/
int	set_sigignr(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}

/*
set signal handler to default behavior
SIGINT to SIG_DFL, SIGQUIT to SIG_DFL
*/
int	set_sigdflt(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	return (0);
}
