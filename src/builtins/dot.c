/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:13:39 by aramarak          #+#    #+#             */
/*   Updated: 2025/11/29 11:43:15 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_directory(const char *path)
{
	struct stat	s;

	if (stat(path, &s) < 0)
		return (0);
	return (S_ISDIR(s.st_mode));
}

static int	is_binary_file(const char *path)
{
	int		fd;
	char	buf[2];

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	if (read(fd, buf, 2) == 2)
	{
		if ((unsigned char)buf[0] == 0x7f && buf[1] == 'E')
		{
			close(fd);
			return (1);
		}
	}
	close(fd);
	return (0);
}

int	builtin_dot(char **args, t_env **env)
{
	(void)env;
	if (!args[1])
		return (print_minishell_error(".", NULL, ERR_FNAR, 2));
	if (is_directory(args[1]))
		return (print_minishell_error(".", args[1], ERR_IS_DIR, 126));
	if (access(args[1], F_OK) < 0)
		return (print_minishell_error(".", args[1], ERR_DIR, 1));
	if (is_binary_file(args[1]))
		return (print_minishell_error(".", args[1], ERR_BIN, 1));
	return (0);
}
