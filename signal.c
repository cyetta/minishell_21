/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 09:05:13 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/23 11:39:41 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <readline/readline.h>
#include "minishell.h"

void	sig_hndlr(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 1);
		write(1, "\n", 1);
		rl_redisplay();
	}
}

int	set_signal(t_mshell *data)
{
	(void)data;
	signal(SIGINT, sig_hndlr);
	signal(SIGQUIT, SIG_IGN);
}