/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:36:08 by cyetta            #+#    #+#             */
/*   Updated: 2022/10/01 04:45:16 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SIGNAL_H
# define FT_SIGNAL_H
# define FT_SIG_IGN 1
# define FT_SIG_DFL 2
# define FT_SIG_HDL 3

int	set_sigfork(char *cmd);
int	set_signal(int type);
#endif