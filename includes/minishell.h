/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:23:38 by aramarak          #+#    #+#             */
/*   Updated: 2025/08/26 21:56:39 by aramarak         ###   ########.fr       */
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

// ====== types ======
typedef struct s_shell
{
	char	**env;
	int		last_status;
}	t_shell;

// ===== env utils =====
size_t	ms_env_count(char **envp);
char	**ms_env_dup(char **envp);
void	ms_env_free(char **env);
void	ms_env_print(char **env);
char   *ms_getenv(char **env, const char *name);

// ===== signals =====
void	setup_signals(void);

// ===== prompt =====
char	*read_prompt(void);

// ===== parser =====
// Простая версия: разбивка по пробелам/табам (без кавычек пока)
char	**parse_input(const char *line);
void	free_argv(char **argv);

/* path resolver */
char	*find_in_path(const char *cmd, char **env);

// ===== executor (пока заглушка) =====
int		execute_command(char **argv, t_shell *sh);

#endif // MINISHELL_H