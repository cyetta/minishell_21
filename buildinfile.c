/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildinfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 00:09:10 by macbook           #+#    #+#             */
/*   Updated: 2022/09/01 23:53:57 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//pipex->world_child->execute->....
void	execute(t_mshell *data)
{
	char	**paths;
	char	*name;
	pid_t	p;

	if (exec_built(data))
		return ;
	p = fork();
	if (!p)
	{
		paths = get_paths(line.envp);
		if (!paths)
			err_msg("minishell:command not found", 3);
		name = find_data(paths, data->args);
		ft_free(paths);
		if (execve(name, data->args, line.envp) == -1)
			err_msg("minishell:command not found", 3);
		if (name)
			free(name);
	}
	else
		waitpid(p, &global, 0);
}

void	ft_free(char **mass)
{
	int	sizemass;

	sizemass = 0;
	while (mass[sizemass])
	{
		free(mass[sizemass]);
		sizemass++;
	}
	free(mass);
}

char	**get_paths(char **envp)
{
	char	**paths;
	char	*tmp;
	int		i;

	i = 0;
	while (*envp)
	{
		if (!ft_strncmp(*envp, "PATH=", 5))
		{
			paths = ft_split(*envp + 5, ':');
			while (paths[i])
			{
				tmp = ft_strjoin(paths[i], "/");
				free(paths[i]);
				paths[i] = ft_strdup(tmp);
				free(tmp);
				i++;
			}
			return (paths);
		}
		envp++;
	}
	return (0);
}

char	*find_data(char **paths, char **data_flags)
{
	char	*data;
	int		i;

	i = 0;
	data = ft_strdup(data_flags[0]);
	if (!access(data_flags[0], F_OK))
		return (data);
	free(data);
	while (paths[i])
	{
		data = ft_strjoin(paths[i], data_flags[0]);
		if (!access(data, F_OK))
			return (data);
		else
			free(data);
		i++;
	}
	if (!data)
		err_msg("minishell: command not found", 3);
	return (NULL);
}

int	exec_built(t_mshell *data)
{
	int	i;

	i = 1;
	if (!ft_strncmp(data->args[0], "exit", ft_strlen(data->args[0])))
		i = 1;
	else if (!ft_strncmp(data->args[0], "echo", ft_strlen(data->args[0])))
		ft_echo(data);
	else if (!ft_strncmp(data->args[0], "pwd", ft_strlen(data->args[0])))
		ft_pwd();
	else if (!ft_strncmp(data->args[0], "env", ft_strlen(data->args[0])))
		ft_env();
	else if (!ft_strncmp(data->args[0], "export", ft_strlen(data->args[0])))
		line.envp = ft_export(data->args);
	else if (!ft_strncmp(data->args[0], "unset", ft_strlen(data->args[0])))
		line.envp = ft_unset(data->args, line.envp);
	else if (!ft_strncmp(data->args[0], "cd", ft_strlen(data->args[0])))
		i = 1;
	else
		i = 0;
	return (i);
}
//ft_echo
void	ft_echo(t_mshell *data)
{
	int	i;

	i = 1;
	if (!data->args[1])
	{
		printf("\n");
		return ;
	}
	while (data->args[i] && !ft_strncmp(data->args[i], "-n",
			ft_strlen(data->args[i])))
		i++;
	while (data->args[i])
	{
		printf("%s", data->args[i]);
		if (data->args[i + 1])
			printf(" ");
		i++;
	}
	if (ft_strncmp(data->args[1], "-n", ft_strlen(data->args[1])))
		printf("\n");
}
//ft_pwd
void	ft_pwd(void)
{
	char	cwd[4096];

	getcwd(cwd, 4097);
	printf("%s\n", cwd);
}
//ft_env
void	ft_env(void)
{
	int	i;

	i = 0;
	while (line.envp[i])
	{
		if (!ft_strchr(line.envp[i], '='))
			i++;
		else
		{
			printf("%s\n", line.envp[i]);
			i++;
		}
	}
}
//ft_exit
void	ft_exit(t_mshell *data, int ifexit)
{
	int	i;

	i = 0;
	if (ifexit && !(data->args[1] && data->args[2]))
		printf("exit\n");
	if (data->args[1] && data->args[2])
		err_msg("exit: too many arguments", 3);
	if (data->args[1])
	{
		while (ft_isdigit(data->args[1][i]))
			i++;
		if ((size_t)i != ft_strlen(data->args[1]))
			err_msg("exit: numeric argument required", 3);
	}
	if (ifexit && !(data->args[1] && data->args[2]))
	{
		if (!data->args[1])
			exit(0);
		else if ((size_t)i != ft_strlen(data->args[1]))
			exit(255);
		else
			exit(ft_atoi(data->args[1]) % 256);
	}
}
//proverka na exit&cd
void	check_cd_exit(t_mshell *data, int n)
{
	int	dodata;

	if (ft_datalen(data) == 1 && !n)
		dodata = 1;
	else
		dodata = 0;
	if (!ft_strncmp(data->args[0], "exit", ft_strlen(data->args[0])))
		ft_exit(data, dodata);
	if (!ft_strncmp(data->args[0], "cd", ft_strlen(data->args[0])))
		line.envp = ft_todir(data->args, dodata);
}
//cd
char	**ft_todir(char **args, int ifcd)
{
	char	*path;
	char	*old_path;
	char	cwd[4096];

	old_path = ft_strdup(getcwd(cwd, 4097));
	if (ifcd && (!args[1] || !ft_strncmp(args[1], "~", ft_strlen(args[1]))))
		chdir(getenv("HOME"));
	else if (args[1])
	{
		if (ft_strncmp(args[1], "~/", 2) == 0)
		{
			chdir(getenv("HOME"));
			path = ft_strdup(ft_strchr_for_mini(args[1], '/'));
			validpath(path, old_path, ifcd);
			free(path);
		}
		else
			validpath(args[1], old_path, ifcd);
	}
	else if (ifcd && !ft_strncmp(args[1], "..", ft_strlen("..")))
		chdir("..");
	if (ifcd)
		line.envp = cd_pwd_oldpwd(old_path);
	return (line.envp);
}

char	*ft_strchr_for_mini(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' || s[i] == c)
	{
		if (s[i] == c)
			return ((char *)s + (i + 1));
		i++;
	}
	return (NULL);
}

char	**cd_pwd_oldpwd(char *old_path)
{
	char	*pwd;
	char	cwd[4096];
	char	*new_old_path;

	new_old_path = ft_strjoin("OLDPWD=", old_path);
	free(old_path);
	pwd = ft_strjoin("PWD=", getcwd(cwd, 4096));
	line.envp = replace_envp_el(line.envp, pwd, "PWD=");
	if (check_unset("OLDPWD=", line.envp))
		line.envp = replace_envp_el(line.envp, new_old_path, "OLDPWD=");
	else
		line.envp = export_envp(line.envp, new_old_path, 1);
	free(new_old_path);
	free(pwd);
	return (line.envp);
}

void	ifs(int j, int i, char *args, char *str)
{
	if (j == 1 && i)
		chdir(str);
	else if (j != 1)
		errmsg("minishell: cd: ", args, ": No such file or directory", -1);
	else if (j == 1 && !i)
		errmsg("minishell: cd: ", args, ": Not a directory", -1);
}

void	inside_validpath(char *str, int j, char *old_path, char *args)
{
	DIR				*dir;
	struct dirent	*entry;
	struct stat		status;
	int				ifcd;
	int				i;

	ifcd = j;
	entry = NULL;
	dir = opendir("./");
	entry = readdir(dir);
	j = 0;
	while (entry != NULL)
	{
		if (ft_strncmp(str, entry->d_name, ft_strlen(entry->d_name)) == 0)
		{
			stat(str, &status);
			j = 1;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	i = S_ISDIR(status.st_mode);
	ifs(j, i, args, str);
	if ((j != 1 || !i) || !ifcd)
		chdir(old_path);
}

void	validpath(char *args, char *old_path, int ifcd)
{
	char	**str;
	int		i;
	int		j;

	j = 0;
	i = ft_strlen(args);
	while (args[j] && args[j] != '/' )
		j++;
	if (j != i)
		str = ft_split(args, '/');
	else
		str = ft_split(args, '\0');
	i = 0;
	while (str[i])
	{
		j = ifcd;
		inside_validpath(str[i], j, old_path, args);
		i++;
	}
	ft_free(str);
}

char	**after_unset(char *args, char **envp)
{
	int		i;
	int		j;
	char	**new_mass;

	new_mass = malloc(sizeof(char *) * size_mass(envp));
	if (!new_mass)
		return (NULL);
	i = 0;
	j = 0;
	while (envp[j])
	{
		if (ft_strncmp(envp[j], args, ft_strlen(args)) == 0)
			j++;
		if (!envp[j])
			break ;
		new_mass[i] = ft_strdup(envp[j]);
		i++;
		j++;
	}
	new_mass[i] = NULL;
	ft_free(envp);
	return (new_mass);
}

int	check_unset(char *args, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], args, ft_strlen(args)) == 0)
			return (1);
		i++;
	}
	return (0);
}
//unset
char	**ft_unset(char **args, char **envp)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (args[++i])
	{
		j = 0;
		k = 0;
		while (args[i][j])
		{
			if (args[i][j] == '=')
			{
				errmsg("minishell: unset: `", args[i],
					"': not a valid identifier", -1);
				k = 1;
				break ;
			}
			j++;
		}
		if (k == 0 && check_unset(args[i], envp))
			envp = after_unset(args[i], envp);
	}
	line.status = 0;
	return (envp);
}

char	**replace_envp_el(char **envp, char *args, char *new)
{
	char	**new_mass;
	int		j;

	j = 0;
	new_mass = malloc(sizeof(char *) * (size_mass(envp) + 1));
	if (!new_mass)
		return (NULL);
	while (envp[j])
	{
		if (ft_strncmp(envp[j], new, max(ft_strlen(new),
					ft_sym_export(envp[j]))))
			new_mass[j] = ft_strdup(envp[j]);
		else
			new_mass[j] = ft_strdup(args);
		j++;
	}
	new_mass[j] = NULL;
	ft_free(envp);
	return (new_mass);
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int	ft_sym_export(char *str)
{
	int	j;

	j = 0;
	while (str[j] && str[j] != '=')
		j++;
	return (j);
}

char	**export_envp(char **envp, char *str, int free)
{
	char	**new_mass;
	int		j;

	new_mass = malloc(sizeof(char *) * (size_mass(envp) + 2));
	if (!new_mass)
		return (NULL);
	j = 0;
	while (envp[j])
	{
		new_mass[j] = ft_strdup(envp[j]);
		j++;
	}
	new_mass[j] = ft_strdup(str);
	j++;
	new_mass[j] = NULL;
	if (free)
		ft_free(envp);
	return (new_mass);
}
//export
char	**ft_export(char **args)
{
	int		i;
	int		j;
	char	*new;

	if (!args[1])
		exp_withot_args(line.envp);
	i = 0;
	while (args[++i])
	{
		j = -1;
		new = check_double(args[i], line.envp);
		while (args[i][++j])
		{
			if (!ft_isalpha(args[i][0]) || args[i][0] == '=')
				err_msg("minishell: export: not a valid identifier", 3);
			else
				change_envp(new, args, i);
			break ;
		}
		if (new)
			free(new);
	}
	return (line.envp);
}

void	exp_withot_args(char **envp)
{
	int		i;
	char	**tmpmass;
	char	**before;
	char	**after;

	i = 0;
	tmpmass = new_envp(envp);
	tmpmass = sort_mass_bubble(tmpmass);
	before = mass_quots_before(tmpmass);
	after = mass_quots_after(tmpmass);
	while (tmpmass[i])
	{
		if (!ft_strchr(tmpmass[i], '='))
			printf("declare -x %s\n", before[i]);
		else
			printf("declare -x %s=\"%s\"\n", before[i], after[i]);
		i++;
	}
	ft_free(tmpmass);
	ft_free(before);
	ft_free(after);
}

char	**new_envp(char **envp)
{
	char	**new_mass;
	int		i;

	new_mass = malloc(sizeof(char *) * (size_mass(envp) + 1));
	if (!new_mass)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_mass[i] = ft_strdup(envp[i]);
		i++;
	}
	new_mass[i] = NULL;
	return (new_mass);
}

char	**sort_mass_bubble(char **mass)
{
	int		i;
	int		k;
	int		j;
	char	*tmp;

	i = -1;
	j = size_mass(mass);
	while (++i < (j - 1))
	{
		k = -1;
		while (++k < (j - i - 1))
		{
			if (ft_strncmp(mass[k], mass[k + 1], ft_sym_export(mass[k])) > 0)
			{
				tmp = ft_strdup(mass[k]);
				free(mass[k]);
				mass[k] = ft_strdup(mass[k + 1]);
				free(mass[k + 1]);
				mass[k + 1] = ft_strdup(tmp);
				free(tmp);
			}
		}
	}
	mass[i + 1] = NULL;
	return (mass);
}

char	**mass_quots_before(char **tmpmass)
{
	int		i;
	int		j;
	char	**before;

	before = malloc(sizeof(char *) * (size_mass(tmpmass) + 1));
	if (!before)
		return (NULL);
	i = -1;
	while (tmpmass[++i])
	{
		j = -1;
		before[i] = malloc(sizeof(char) * (ft_sym_export(tmpmass[i]) + 1));
		if (!before[i])
			return (NULL);
		if (!ft_strchr(tmpmass[i], '='))
			before[i] = ft_strdup(tmpmass[i]);
		else
		{
			while (tmpmass[i][++j] != '=')
				before[i][j] = tmpmass[i][j];
			before[i][j] = '\0';
		}
	}
	before[i] = NULL;
	return (before);
}

char	**mass_quots_after(char **tmpmass)
{
	int		i;
	int		j;
	int		k;
	char	**after;

	after = malloc(sizeof(char *) * (size_mass(tmpmass) + 1));
	if (!after)
		return (NULL);
	i = -1;
	while (tmpmass[++i])
	{
		k = 0;
		after[i] = malloc(sizeof(char) * (ft_strlen(tmpmass[i])
					- ft_sym_export(tmpmass[i]) + 1));
		if (!after[i])
			return (NULL);
		j = ft_sym_export(tmpmass[i]);
		while (tmpmass[i][++j] != '\0')
			after[i][k++] = tmpmass[i][j];
		after[i][k] = '\0';
	}
	after[i] = NULL;
	return (after);
}

char	*check_double(char *args, char **envp)
{
	int		i;
	char	*str_tmp;

	i = 0;
	str_tmp = malloc(sizeof(char) * (ft_sym_export(args) + 1));
	if (!str_tmp)
		return (NULL);
	while (args[i] != '\0' && args[i] != '=')
	{
		str_tmp[i] = args[i];
		i++;
	}
	str_tmp[i] = '\0';
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(str_tmp, envp[i], max(ft_strlen(str_tmp),
					ft_sym_export(envp[i]))))
			return (str_tmp);
		i++;
	}
	free(str_tmp);
	return (NULL);
}

void	change_envp(char *new, char **args, int i)
{
	if (new && ft_strrchr(args[i], '='))
		line.envp = replace_envp_el(line.envp, args[i], new);
	else if (!new)
		line.envp = export_envp(line.envp, args[i], 1);
}
