/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:23:38 by aramarak          #+#    #+#             */
/*   Updated: 2025/08/24 15:35:06 by aramarak         ###   ########.fr       */
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

// ===== signals =====
void	setup_signals(void);

// ===== prompt =====
char	*read_prompt(void);

// ===== parser =====
// Простая версия: разбивка по пробелам/табам (без кавычек пока)
char	**parse_input(const char *line);
void	free_argv(char **argv);

// ===== executor (пока заглушка) =====
int		execute_command(char **argv, t_shell *sh);

#endif // MINISHELL_H