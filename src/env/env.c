#include "minishell.h"
#include "env.h"

/**
 * @brief Frees the entire environment linked list.
 *
 * Iterates through the linked list of t_env structures and frees the memory
 * allocated for the key, the value, and the node itself. After this call,
 * the passed pointer becomes invalid since all nodes in the list are freed.
 *
 * @param env Pointer to the head of the environment linked list.
 *
 * @return This function does not return a value.
 *
 * @note Should be called before program termination or when the whole
 *       environment list is no longer needed.
 * @warning After calling this function, the pointer 'env' must not be used.
 */
void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}