/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 22:12:22 by aramarak          #+#    #+#             */
/*   Updated: 2025/08/26 22:14:21 by aramarak         ###   ########.fr       */
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

char	*find_in_path(const char *cmd, char **env)
{
	char *path;
	char *p, *next;
	size_t len;

	if (!cmd || !*cmd)
		return NULL;
	path = ms_getenv(env, "PATH");
}