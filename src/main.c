/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:23:31 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/25 19:35:34 by aramarak         ###   ########.fr       */
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

static void	run_single_command(t_cmd *cmd, t_env **env)
{
	pid_t	pid;
	int		status;
	int		exit_code;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return ;
	if (is_builtin(cmd->argv[0]))
	{
		if (ft_strcmp(cmd->argv[0], "exit") == 0
			|| ft_strcmp(cmd->argv[0], "cd") == 0
			|| ft_strcmp(cmd->argv[0], "export") == 0
			|| ft_strcmp(cmd->argv[0], "unset") == 0)
		{
			run_builtin(cmd->argv, env);
			return ;
		}
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return ;
	}
	else if (pid == 0)
	{
		if (cmd->redir && apply_redirections(cmd) != 0)
			_exit(1);
		if (is_builtin(cmd->argv[0]))
			run_builtin(cmd->argv, env);
		else
			execute_command(cmd->argv, *env);
		_exit(0);
	}
	else
		waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_code = 128 + WTERMSIG(status);
	else
		exit_code = 1;
	last_status(1, exit_code);
}

/**
 * @brief Process and execute a single line of shell input.
 * This function handles parsing the input line into commands,
 * executing them (either as a pipeline or a single command),
 * and cleaning up resources afterwards.
 * 
 */
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
		run_shell_line(line, env, locals);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	t_env	*locals;

	(void)argc;
	(void)argv;
	env = init_env(envp);
	locals = init_locals();
	last_status(1, 0);
	if (!env)
	{
		perror("minishell: failed to init env");
		return (1);
	}
	setup_signals();
	run_shell_loop(&env, &locals);
	free_env(env);
	free_locals(locals);
	return (EXIT_SUCCESS);
}
