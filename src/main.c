/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:23:31 by aramarak          #+#    #+#             */
/*   Updated: 2025/10/06 01:39:34 by aramarak         ###   ########.fr       */
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

static int	is_direct_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strcmp(cmd, "exit")
		|| !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset"));
}

static int	exec_child_process(t_cmd *cmd, t_env **env, int i)
{
	int	exit_code;

	signal_default();
	if (cmd->redir && apply_redirections(cmd) != 0)
		_exit(1);
	if (is_builtin(cmd->argv[i]))
		exit_code = run_builtin(&cmd->argv[i], env);
	else
		exit_code = execute_command(&cmd->argv[i], *env);
	_exit(exit_code);
}

static int	wait_for_child(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

void	run_single_command(t_cmd *cmd, t_env **env)
{
	pid_t	pid;
	int		exit_code;
	int		i;

	if (!cmd || !cmd->argv)
		return ;
	i = 0;
	while (cmd->argv[i] && cmd->argv[i][0] == '\0')
		i++;
	if (!cmd->argv[i])
		return ;
	if (is_direct_builtin(cmd->argv[i]))
		return ((void)run_builtin(&cmd->argv[i], env));

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
			break ;
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
	return (EXIT_SUCCESS);
}
