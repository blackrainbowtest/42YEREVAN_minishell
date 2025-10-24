/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:23:31 by aramarak          #+#    #+#             */
/*   Updated: 2025/10/25 02:08:43 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_single_command(t_cmd *cmd, t_env **env)
{
	pid_t	pid;
	int		exit_code;
	int		i;

	if (!cmd || !cmd->argv)
		return ;
	if (prepare_heredocs(cmd) < 0)
		return ;
	i = 0;
	while (cmd->argv[i] && cmd->argv[i][0] == '\0')
		i++;
	if (!cmd->argv[i])
		return ;
	if (is_direct_builtin(cmd->argv[i]))
		return ((void)run_builtin(&cmd->argv[i], env));
	// TODO: make diff function
	if (cmd->argv && cmd->argv[0])
	{
		int	last = 0;
		while (cmd->argv[last + 1])
			last++;
		ft_setenv(env, "_", cmd->argv[last], 1);
	}
	in_child_process(1, 1);
	pid = fork();
	if (pid < 0)
		return ((void)perror("fork"));
	if (pid == 0)
		exec_child_process(cmd, env, i);
	exit_code = wait_for_child(pid);
	in_child_process(1, 0);
	last_status(1, exit_code);
}

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
			exit(last_status(0, 0));
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
