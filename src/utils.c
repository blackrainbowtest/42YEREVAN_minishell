/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:33:48 by aramarak          #+#    #+#             */
/*   Updated: 2025/10/31 02:13:54 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_exec_path(char *path)
{
	struct stat	st;

	if (stat(path, &st) != 0)
		return (print_minishell_error(MINISHELL, path, ERR_DIR, 127));
	if (S_ISDIR(st.st_mode))
		return (print_minishell_error(MINISHELL, path, ERR_IS_DIR, 126));
	if (access(path, X_OK) != 0)
		return (print_minishell_error(MINISHELL, path, ERR_PERM, 126));
	return (0);
}

int	is_blank(const char *s)
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

int	is_direct_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strcmp(cmd, "exit")
		|| !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset"));
}

int	exec_child_process(t_cmd *cmd, t_env **env, int i)
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

int	wait_for_child(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}
