/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 12:30:09 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/06 12:30:09 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

/* env core */
t_env		*init_env(char **envp);
void		free_env(t_env *env);

/* getters / setters */
char		*ft_getenv(t_env *env, const char *key);
int			ft_setenv(t_env **env, const char *key,
				const char *value, int overwrite);
int			ft_unsetenv(t_env **env, const char *key);

/* ===== env_local_utils.c ===== */
char		*ft_getvar(t_env *locals, t_env *env, const char *key);
int			is_assignment_token(const char *str);
int			move_local_to_env(t_env **locals, t_env **env, const char *key);

/* ===== env_local.c ===== */
char		*ft_getlocal(t_env *locals, const char *key);
int			ft_setlocal(t_env **locals, const char *key,
				const char	*value, int overwrite);
int			ft_unsetlocal(t_env **locals, const char *key);
void		free_locals(t_env *locals);
int			handle_assignment(t_env **locals, const char *token);

/* ===== env_create_utils.c ===== */
t_env		*create_local_node(const char *key, const char *value);
t_env		*init_locals(void);

#endif