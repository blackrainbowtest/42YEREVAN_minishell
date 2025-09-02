/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:33:48 by aramarak          #+#    #+#             */
/*   Updated: 2025/08/26 21:55:28 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ms_env_count(char **envp)
{
	size_t	n;

	if (!envp)
		return (0);
	n = 0;
	while (envp[n])
		n++;
	return (n);
}


char	**ms_env_dup(char **envp)
{
	size_t	n;
	size_t	i;
	char	**cp;

	n = ms_env_count(envp);
	cp = (char **)malloc((n + 1) * sizeof(char *));
	if (!cp)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < n)
	{
		cp[i] = strdup(envp[i]);
		if (!cp[i])
		{
			perror("strdup");
			while (i > 0)
				free(cp[--i]);
			free(cp);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	cp[n] = NULL;
	return (cp);
}

void	ms_env_free(char **env)
{
	size_t	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
}

void	ms_env_print(char **env)
{
	size_t	i;

	i = 0;
	while (env && env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

char	*ms_getenv(char **env, const char *name)
{
	size_t	nlen;
	size_t	i;

	if (!env || !name)
		return (NULL);
	nlen = strlen(name); // LIBFT
	i = -1;
	while (env[++i])
	{
		if (strncmp(env[i], name, nlen) == 0 && env[i][nlen] == '=') // LIBFT
			return (env[i] + nlen + 1);
	}
	return (NULL);
}
