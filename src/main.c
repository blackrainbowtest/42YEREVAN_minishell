/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:23:31 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/12 01:23:47 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

static int	is_blank(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (1);
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

static int	handle_builtin_or_exec(char **argv, t_env **env)
{
	if (strcmp(argv[0], "echo") == 0)
		return (builtin_echo(argv));
	if (strcmp(argv[0], "cd") == 0)
		return (builtin_cd(argv, env));
	if (strcmp(argv[0], "pwd") == 0)
		return (builtin_pwd(*env));
	if (strcmp(argv[0], "env") == 0)
		return (builtin_env(*env));
	if (strcmp(argv[0], "export") == 0)
		return (builtin_export(argv, env));
	if (strcmp(argv[0], "unset") == 0)
		return (builtin_unset(argv, env));
	if (strcmp(argv[0], "exit") == 0)
		return (builtin_exit(argv));
	return (execute_command(argv, *env));
}

static void	run_shell(t_env **env)
{
	char	*line;
	char	**args;

	while (1)
	{
		line = read_prompt();
		if (!line)
			break ;
		if (is_blank(line))
		{
			free(line);
			continue ;
		}
		args = parse_input(line);
		free(line);
		if (!args)
			continue ;
		handle_builtin_or_exec(args, env);
		free_argv(args);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc;
	(void)argv;
	env = init_env(envp);
	if (!env)
	{
		perror("minishell: failed to init env");
		return (1);
	}
	setup_signals();
	run_shell(&env);
	free_env(env);
	return (0);
}
