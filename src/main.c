/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:23:31 by aramarak          #+#    #+#             */
/*   Updated: 2025/11/04 00:28:08 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_shell_line(char *line, t_env **env, t_env **locals)
{
	t_cmd	*cmds;

	if (is_blank(line))
	{
		free(line);
		return ;
	}
	cmds = parse_line(line, *env, locals);
	free(line);
	if (!cmds)
		return ;
	if (cmds->next)
		execute_pipeline(cmds, env);
	else
		run_single_command(cmds, env);
	free_cmds(cmds);
}

static void	run_shell_loop(t_env **env, t_env **locals)
{
	char	*line;

	while (1)
	{
		line = read_prompt();
		if (!line)
		{
			if (isatty(STDIN_FILENO))
				ft_putendl_fd("exit", STDERR_FILENO);
			clean_and_exit(last_status(0, GET));
		}
		if (*line)
			add_history(line);
		run_shell_line(line, env, locals);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	t_env	*locals;

	(void)argc;
	(void)argv;
	setup_signals();
	env = init_env(envp);
	locals = init_locals();
	env_storage(env, SET);
	locals_storage(locals, SET);
	last_status(1, 0);
	in_child_process(1, 0);
	if (!env)
	{
		perror("minishell: failed to init env");
		return (1);
	}
	run_shell_loop(&env, &locals);
	free_env(env);
	free_locals(locals);
	clear_history();
	return (last_status(0, 0));
}
