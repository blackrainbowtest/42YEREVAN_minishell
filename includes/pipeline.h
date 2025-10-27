/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:49:26 by aramarak          #+#    #+#             */
/*   Updated: 2025/10/25 02:08:20 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
# define PIPELINE_H

typedef struct s_env	t_env;
typedef struct s_cmd	t_cmd;

/* ===== child_process.c ===== */
void	child_process(t_cmd *cmd, int in_fd, int out_fd, t_env **env);

/* ===== execute_pipeline.c ===== */
int		execute_pipeline(t_cmd *cmds, t_env **env);

/* ===== executor_utils.c ===== */
char	**env_to_envp(t_env *env);
void	free_argv(char **argv);

/* ===== executor.c ===== */
int		execute_command(char **argv, t_env *env);


int		prepare_heredocs(t_cmd *cmds);
#endif