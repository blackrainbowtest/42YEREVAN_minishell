/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:23:38 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/11 19:54:38 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ====== system headers ======
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>

// GNU Readline
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"
# include "defs.h"
# include "env.h"
# include "builtins.h"

// ===== signals =====
void	setup_signals(void);

// ===== prompt =====
char	*read_prompt(void);

// ===== parser =====
// Простая версия: разбивка по пробелам/табам (без кавычек пока)
char	**parse_input(const char *line);
void	free_argv(char **argv);

/* path resolver */
char	*find_in_path(const char *cmd, t_env *env);

// ===== executor (пока заглушка) =====
int		execute_command(char **argv, t_env *env);
char	**env_to_envp(t_env *env);

#endif // MINISHELL_H