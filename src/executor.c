/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:38:18 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/07 03:48:15 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **env_to_envp(t_env *env)
{
	int		count;
	t_env	*tmp;
	char	**envp;
	char	*pair;
	int		i;
	size_t	len;

	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	tmp = env;
	i = 0;
	while (tmp)
	{
		len = ft_strlen(tmp->key) + 1 + (tmp->value ? strlen(tmp->value) : 0);
		pair = malloc(len + 1);
		if (!pair)
			return (NULL);
		ft_strlcpy(pair, tmp->key, len + 1);
		ft_strlcat(pair, "=", len + 1);
		if (tmp->value)
			strlcat(pair, tmp->value, len + 1);
		envp[i++] = pair;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}

static int	spawn_and_wait(char *path, char **argv, t_env *env)
{
	pid_t	pid;
	int		status;
	char	**envp;

	envp = env_to_envp(env);
	if (!env)
		return (1);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		execve(path, argv, envp);
		perror("execve");
		_exit (126);
	}
	free_argv(envp);
	if (waitpid(pid, &status, 0) < 0)
	{
		perror("waitpid");
		return (1);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

int	execute_command(char **argv, t_env *env)
{
	char	*path;
	int		code;

	if (!argv || !argv[0])
		return (0);
	if (strcmp(argv[0], "echo") == 0)
		return (builtin_echo(argv));
	// TODO: cd, pwd, env, export, unset, exit
	path = find_in_path(argv[0], env);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
	code = spawn_and_wait(path, argv, env);
	free(path);
	return (code);
}
