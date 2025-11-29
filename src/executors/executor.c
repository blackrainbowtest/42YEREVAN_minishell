/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:38:18 by aramarak          #+#    #+#             */
/*   Updated: 2025/10/24 00:49:23 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_child(char *path, char **argv, char **envp)
{
	int	exit_code;

	signal_default();
	if (!path || !path[0])
		_exit(126);
	if (access(path, F_OK) != 0)
		_exit(print_minishell_error(argv[0], NULL, ERR_DIR, 127));
	exit_code = check_exec_path(path);
	if (exit_code != 0)
		_exit(last_status(1, exit_code));
	execve(path, argv, envp);
	perror("execve");
	_exit(126);
}

int	execute_child(char *path, char **argv, char **envp)
{
	pid_t	pid;

	in_child_process(1, 1);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
		run_child(path, argv, envp);
	return (pid);
}

static char	*first_nonempty(char **argv)
{
	int		i;

	i = 0;
	if (!argv)
		return (NULL);
	while (argv[i] && argv[i][0] == '\0')
		i++;
	if (!argv[i])
		return (NULL);
	return (argv[i]);
}

static char	*resolve_cmd_path(char *cmd, t_env *env)
{
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	return (find_in_path(cmd, env));
}

int	execute_command(char **argv, t_env *env)
{
	char	*cmd;
	char	*path;
	int		exit_code;

	cmd = first_nonempty(argv);
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "..") == 0)
		return (print_minishell_error(cmd, NULL, ERR_CNF2, 127));
	path = resolve_cmd_path(cmd, env);
	if (!path)
		return (print_minishell_error(cmd, NULL, ERR_CNF2, 127));
	exit_code = check_exec_path(path);
	if (exit_code != 0)
	{
		free(path);
		return (last_status(1, exit_code));
	}
	exit_code = spawn_and_wait(path, argv, env);
	free(path);
	return (exit_code);
}
