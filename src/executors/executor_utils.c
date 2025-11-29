/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:52:48 by aramarak          #+#    #+#             */
/*   Updated: 2025/11/29 13:29:27 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_env(t_env *env)
{
	int		count;
	t_env	*tmp;

	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

static char	*make_env_pair(t_env *node)
{
	size_t	len;
	char	*pair;

	len = ft_strlen(node->key) + 1;
	if (node->value)
		len += ft_strlen(node->value);
	pair = malloc(len + 1);
	if (!pair)
		return (NULL);
	ft_strlcpy(pair, node->key, len + 1);
	ft_strlcat(pair, "=", len + 1);
	if (node->value)
		ft_strlcat(pair, node->value, len + 1);
	return (pair);
}

char	**env_to_envp(t_env *env)
{
	char	**envp;
	t_env	*tmp;
	int		i;

	envp = malloc(sizeof(char *) * (count_env(env) + 1));
	if (!envp)
		return (NULL);
	tmp = env;
	i = 0;
	while (tmp)
	{
		envp[i] = make_env_pair(tmp);
		if (!envp[i])
		{
			free_argv(envp);
			return (NULL);
		}
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	free_argv(char **argv)
{
	size_t	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(argv);
}

int	spawn_and_wait(char *path, char **argv, t_env *env)
{
	pid_t	pid;
	int		status;
	char	**envp;
	int		exit_code;

	envp = env_to_envp(env);
	if (!envp)
		return (1);
	pid = execute_child(path, argv, envp);
	free_argv(envp);
	in_child_process(1, 0);
	if (waitpid(pid, &status, 0) < 0)
	{
		perror("waitpid");
		return (last_status(1, 1));
	}
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_code = 128 + WTERMSIG(status);
	else
		exit_code = 1;
	last_status(1, exit_code);
	return (exit_code);
}
