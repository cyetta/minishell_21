/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:37:11 by macbook           #+#    #+#             */
/*   Updated: 2022/09/26 14:18:59 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"builtins.h"

/*char	*get_env_var(t_prgexec *cmd, char *var)
{
	int		i;
	char	*tmp;

	i = -1;
	while (cmd->argv[++i])
	{
		tmp = ft_strjoinch(var, '=');
		if (ft_strstartswith(cmd->argv[i], tmp))
		{
			free(tmp);
			return (ft_strchr(cmd->argv[i], '=') + 1);
		}
		free(tmp);
	}
	return (NULL);
}

char	*ft_strjoinch(char const *s1, char c)
{
	char	*new_str;
	size_t	i;
	size_t	s1_len;

	if (!s1 || !c)
		return (NULL);
	s1_len = ft_strlen(s1);
	new_str = ft_strnew(s1_len + 1);
	if (!new_str)
		return (NULL);
	i = -1;
	while (++i < s1_len)
		*(new_str + i) = *(s1 + i);
	*(new_str + i) = c;
	return (new_str);
}

int	ft_strstartswith(char *s1, char *s2)
{
	int	i;

	i = -1;
	while (s2[++i])
		if (s1[i] != s2[i])
			return (0);
	return (1);
}*/
