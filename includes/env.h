#ifndef ENV_H
# define ENV_H

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}   t_env;

/* env core */
t_env	*init_env(char **envp);
void	free_env(t_env *env);

/* getters / setters */
char	*ft_getenv(t_env *env, const char *key);
int		ft_setenv(t_env **env, const char *key, const char *value, int overwrite);
int		ft_unsetenv(t_env **env, const char *key);

#endif