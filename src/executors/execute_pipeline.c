/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:40:33 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/25 21:08:01 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_process(t_cmd *cmd, int in_fd, int out_fd, t_env **env)
{
	char	**envp;
	char	*path;

	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	if (cmd->redir)
	{
		if (apply_redirections(cmd) != 0)
			_exit(1);
	}
	if (is_builtin(cmd->argv[0]))
	{
		run_builtin(cmd->argv, env);
		_exit(0);
	}
	path = find_in_path(cmd->argv[0], *env);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		_exit(127);
	}
	envp = env_to_envp(*env);
	if (cmd->argv[0] == NULL || cmd->argv[0][0] == '\0')
		return ;
	execve(path, cmd->argv, envp);
	perror("execve");
	free_argv(envp);
	free(path);
	_exit(126);
}

int	execute_pipeline(t_cmd *cmds, t_env **env)
{
	t_cmd	*cur;
	int		pipe_fd[2];
	int		in_fd;
	pid_t	pid;
	int		status;
	int		last_status;

	cur = cmds;
	in_fd = STDIN_FILENO;
	last_status = 0;
	while (cur)
	{
		if (cur->next && pipe(pipe_fd) < 0)
		{
			perror("pipe");
			return (1);
		}
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return (1);
		}
		else if (pid == 0)
		{
			if (cur->next)
				close(pipe_fd[0]);
			child_process(cur, in_fd, cur->next ? pipe_fd[1] : STDOUT_FILENO, env);
		}
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		if (cur->next)
		{
			close(pipe_fd[1]);
			in_fd = pipe_fd[0];
		}
		cur = cur->next;
	}
	while (wait(&status) > 0)
		last_status = WIFEXITED(status) ? WEXITSTATUS(status) : 1;
	return (last_status);
}
