/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:23:31 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/17 00:13:20 by aramarak         ###   ########.fr       */
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
		{
			run_builtin(cmd->argv, env);
			_exit(0);
		}
		else
		{
			execute_command(cmd->argv, *env);
			_exit(0);
		}
	}
	else
		waitpid(pid, &status, 0);
}

/**
 * parser_line() -> parser/parser_line.c
 * execute_pipeline() -> pipeline/execute_pipeline.c
 * run_single_command() -> main.c
 * free_cmds() -> parser/parser_utils.c
 */
static void	run_shell_line(char *line, t_env **env)
{
	t_cmd	*cmds;

	if (is_blank(line))
	{
		free(line);
		return ;
	}
	cmds = parse_line(line);
	free(line);
	if (!cmds)
		return ;
	if (cmds->next)
		execute_pipeline(cmds, env);
	else
		run_single_command(cmds, env);
	free_cmds(cmds);
}

static void	run_shell_loop(t_env **env)
{
	char	*line;

	while (1)
	{
		line = read_prompt();
		if (!line)
			break ;
		run_shell_line(line, env);
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
	run_shell_loop(&env);
	free_env(env);
	return (EXIT_SUCCESS);
}
