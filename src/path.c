/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 22:12:22 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/02 22:10:17 by aramarak         ###   ########.fr       */
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
		memcpy(dir, seg, len); // LIBFT
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

static char	*precheck_cmd(const char *cmd, char **env, char **path, char **p)
{
	*path = ms_getenv(env, "PATH");
	if (!cmd || !*cmd)
		return (NULL);
	if (strchr(cmd, '/'))  // LIBFT
		return (strdup(cmd));
	if (!*path || !**path)
		return (NULL);
	*p = *path;
	return ((char *)1);
}

char	*find_in_path(const char *cmd, char **env)
{
	char	*path;
	char	*p;
	char	*next;
	char	*full;
	char	*check;

	check = precheck_cmd(cmd, env, &path, &p);
	if (!check || check != (char *)1)
		return (check);
	while (*p)
	{
		next = strchr(p, ':'); // LIBFT
		if (!next)
			next = p + strlen(p); // LIBFT
		full = try_path_segment(p, (size_t)(next - p), cmd);
		if (full)
			return (full);
		p = next;
		if (*next)
			p = next + 1;
	}
	return (NULL);
}
