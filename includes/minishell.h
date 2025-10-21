/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:23:38 by aramarak          #+#    #+#             */
/*   Updated: 2025/10/04 10:07:34 by aramarak         ###   ########.fr       */
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
# include "parser.h"
# include "pipeline.h"
# include "redirections.h"
# include "debug.h"
# include "status.h"
# include "token.h"
# include "limits.h"

// ===== signals =====
void	setup_signals(void);
void	signal_ctlc_heredoc(int sig);
void	signal_default(void);

// ===== prompt =====
char	*read_prompt(void);

// ===== path =====
char	*find_in_path(const char *cmd, t_env *env);

// ===== utils =====
int		check_exec_path(char *path);
int		is_blank(const char *s);
int		is_direct_builtin(char *cmd);
int		exec_child_process(t_cmd *cmd, t_env **env, int i);
int		wait_for_child(pid_t pid);

#endif // MINISHELL_H