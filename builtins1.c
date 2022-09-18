/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:21:39 by cyetta            #+#    #+#             */
/*   Updated: 2022/09/18 21:36:21 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_util.h"
#include "builtins.h"
#include "minishell.h"

/*
Check command for builtin
return builtin number or 0
*/
int	is_builtin(t_prgexec *cmd)
{
	static char	*bltin = "echo    cd      pwd     export  unset   env     exit";
	char		*subs;

	if (!cmd->argv[0])
		return (0);
	subs = ft_strnstr(bltin, cmd->argv[0], ft_strlen(bltin));
	if (subs)
		return (((subs - bltin) >> 3) + 1);
	if (!ft_strncmp(cmd->argv[0], "exit", ft_strlen(cmd->argv[0])))
		builtin_exit(cmd);
	else if (!ft_strncmp(cmd->argv[0], "echo", ft_strlen(cmd->argv[0])))
		builtin_echo(cmd);
	else if (!ft_strncmp(cmd->argv[0], "pwd", ft_strlen(cmd->argv[0])))
	{
		builtin_pwd();
		printf("11234213412341234123412341234123412341234123\n");
	}
	else if (!ft_strncmp(cmd->argv[0], "env", ft_strlen(cmd->argv[0])))
		builtin_env(cmd);
	return (0);
}

/*
echo with option -n
*/
void	builtin_echo(t_prgexec *cmd)
{
	int	i;

	i = 1;
	if (!cmd->argv[1])
	{
		printf("\n");
		return ;
	}
	while (cmd->argv[i] && !ft_strncmp(cmd->argv[i], "-n",
			ft_strlen(cmd->argv[i])))
		i++;
	while (cmd->argv[i])
	{
		printf("%s", cmd->argv[i]);
		if (cmd->argv[i + 1])
			printf(" ");
		i++;
	}
	if (ft_strncmp(cmd->argv[1], "-n", ft_strlen(cmd->argv[1])))
		printf("\n");
}

/*
cd with only a relative or absolute path
 */
int	builtin_cd(t_prgexec *cmd)
{
	printf("this is %s\n", cmd->execmd);
	return (0);
}

/*
pwd with no options
 */
void	builtin_pwd(void)
{
	char	pwd[4096];

	getcwd(pwd, 4097);
	printf("%s\n", pwd);
}
