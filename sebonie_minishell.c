/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sebonie_minishell                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebonie <sebonie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:26:09 by sebonie           #+#    #+#             */
/*   Updated: 2022/06/14 15:26:10 by sebonie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_lst
{
	int				type;
	char			*value;
	char			**cmd;
	int				str_position;
	struct s_lst	*next;
}					t_lst;


void	init_env(char **in_env, t_env **env)
{
	t_env	*tmp;
	int		i;

	i = -1;
	while (in_env[++i])
	{
		tmp = ft_calloc(1, sizeof(t_env));
		tmp->key = get_env_key(in_env[i]);
		tmp->value = get_env_value(in_env[i]);
		tmp->next = NULL;
		if (*env == NULL)
			*env = tmp;
		else
			find_last_env(*env)->next = tmp; //- func that finds last vals if you paste second command
	}
}

int	cycle(char *line, t_env *env, char **in_env, t_lst *tokens)
{
	t_lst	*pipelines;

	signal_handler();
	pipelines = NULL;
	if (get_comandline(line, NULL))
	{
		freeenv(env);
		free(line);
		rl_clear_history();
		exit(0);
	}
	if (check_line(line) == 1)
	{
		ft_bzero(line, MAXVAL);
		printf("WARNING: Unclosed quote.\n");
		return (1);
	}
	get_tokenlist(line, &tokens);
	expand_env_vars(tokens, env, 0);
	get_pipelinelist(tokens, &pipelines);
	create_outfiles(pipelines);
	add_exit_code(&env, execute(pipelines, env, in_env));
	freelist(tokens, pipelines);
	return (0);
}

int	main(int ac, char **av, char **in_env)
{
	// char	*line; - line
	// t_env	*env; - envs

	(void)av;
	// line = ft_calloc(MAXVAL, sizeof(char)); - maxval some max value that fits good
	if (ac == 1)
	{
		// init_env(in_env, &env);
		// print initial text
	}
	else
	{
		error_message("Error message: too many arguments!");
		exit(1);
	}
	// env = NULL;
	while (1)
		if (cycle(line, env, in_env, NULL))
			continue ;
}