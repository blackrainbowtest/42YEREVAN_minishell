/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 22:12:22 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/11 20:21:21 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_dir_cmd(const char *dir, const char *cmd)
{
	size_t	dl;
	size_t	cl;
	char	*full;

	dl = strlen(dir);
	cl = strlen(cmd);
	full = (char *)malloc(dl + 1 + cl + 1);
	if (!full)
		return (NULL);
	memcpy(full, dir, dl);
	full[dl] = '/';
	memcpy(full + dl + 1, cmd, cl);
	full[dl + 1 + cl] = '\0';
	return (full);
}

static char	*try_path_segment(const char *seg, size_t len, const char *cmd)
{
	char	*dir;
	char	*full;

	if (len > 0)
	{
		dir = (char *)malloc(len + 1);
		if (!dir)
			return (NULL);
		ft_memcpy(dir, seg, len);
		dir[len] = '\0';
		full = join_dir_cmd(dir, cmd);
		free(dir);
	}
	else
		full = join_dir_cmd(".", cmd);
	if (!full)
		return (NULL);
	if (access(full, X_OK) == 0)
		return (full);
	free(full);
	return (NULL);
}

static char	*try_access(const char *path)
{
	if (access(path, X_OK) == 0)
		return (ft_strdup(path));
	return (NULL);
}

char	*find_in_path(const char *cmd, t_env *env)
{
	char	*path_var;
	char	*p;
	char	*next;
	char	*full;

	if (ft_strchr(cmd, '/'))
		return (try_access(cmd));
	path_var = ft_getenv(env, "PATH");
	if (!path_var)
		return (NULL);
	p = path_var;
	while (*p)
	{
		next = ft_strchr(p, ':');
		if (!next)
			next = p + ft_strlen(p);
		full = try_path_segment(p, (size_t)(next - p), cmd);
		if (full)
			return (full);
		p = next;
		if (*next)
			p = next + 1;
	}
	return (NULL);
}
