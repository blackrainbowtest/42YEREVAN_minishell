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
t_env	*init_env(char **envp);
void	free_env(t_env *env);

/* getters / setters */
char	*ft_getenv(t_env *env, const char *key);
int		ft_setenv(t_env **env, const char *key,
			const char *value, int overwrite);
int		ft_unsetenv(t_env **env, const char *key);

// ===== env utils =====
size_t	ms_env_count(char **envp);
char	**ms_env_dup(char **envp);
void	ms_env_free(char **env);
void	ms_env_print(char **env);
char	*ms_getenv(char **env, const char *name);

#endif