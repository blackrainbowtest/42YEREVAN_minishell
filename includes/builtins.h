/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 22:37:27 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/07 22:38:16 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

// ===== builtilns =====
int		builtin_echo(char **args);

int		builtin_cd(char **args, t_env **env);

int		builtin_pwd(t_env *env);

int		builtin_env(char **argv, t_env *env);

int		builtin_export(char **argv, t_env **env);

int		builtin_unset(char **argv, t_env **env);

int		builtin_exit(char **argv);

int		run_builtin(char **argv, t_env **env);
int		is_parent_builtin(char *cmd);
int		is_builtin(char *cmd);

// ===== builtiln utils =====
void	export_update_env(char *arg, t_env **env, char *eq, int *status);
int		env_size(t_env *env);
char	**env_to_keys(t_env *env);
void	sort_env_keys(char **keys);
void	print_sorted_env(t_env *env, char **keys);
int		is_valid_identifier(const char *s);

#endif