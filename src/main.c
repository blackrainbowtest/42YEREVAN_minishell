/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:23:31 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/14 20:19:08 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (!argv || !argv[0])
		return (EXIT_SUCCESS);
	if (is_builtin(argv[0]))
		return (run_builtin(argv, env));
	return (execute_command(argv, *env));
}

static void	run_shell(t_env **env)
{
	char	*line;
	t_cmd	*cmds;
	t_cmd	*cur;

	(void)env;
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
		cmds = NULL;
		cmds = parse_pipeline(line);
		free(line);
		if (!cmds)
			continue;
		if (cmds->next == NULL)
			handle_builtin_or_exec(cmds->argv, env);
		else
		{
			cur = cmds;
			while (cur)
			{
				if (is_builtin(cur->argv[0])
					&& (strcmp(cur->argv[0], "cd") != 0
					&& strcmp(cur->argv[0], "export") != 0
					&& strcmp(cur->argv[0], "unset") != 0
					&& strcmp(cur->argv[0], "exit") != 0))
				{
					execute_pipeline(cmds, env);
					break ;
				}
				else
				{
					if (is_builtin(cur->argv[0]))
					{
						ft_putstr_fd("minishell: warning: builtin cannot run in pipeline: ", 2);
						ft_putendl_fd(cur->argv[0], 2);
					}
					execute_pipeline(cmds, env);
					break ;
				}
			}
		}
		free_cmds(cmds);
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
	return (EXIT_SUCCESS);
}
