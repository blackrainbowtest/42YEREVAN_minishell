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

/**
 * @brief Creates a new environment node from a string entry.
 *
 * Allocates a new t_env structure and initializes its key and value
 * by splitting the input string at the first '=' character. If the '='
 * is not found, the value is set to NULL. The node's next pointer is
 * initialized to NULL.
 *
 * @param entry A string in the format "KEY=VALUE" or "KEY".
 *
 * @return A pointer to the newly allocated t_env node, or NULL if
 *         memory allocation fails.
 *
 * @note The returned node is not added to any list; you must link it
 *       manually if needed.
 * @warning The caller is responsible for freeing the returned node
 *          to avoid memory leaks.
 */
static t_env	*create_env_node(char *entry)
{
	t_env	*new;
	char	*eq;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	eq = strchr(entry, "="); // LIBFT
	if (eq)
	{
		new->key = substr(entry, 0, eq - entry); // LIBFT
		new->value = strdup(eq + 1); // LIBFT
	}
	else
	{
		new->key = strdup(entry); // LIBFT
		new->value = NULL;
	}
	new->next = NULL;
	return (new);
}

/**
 * @brief Initializes the environment linked list from an array of strings.
 *
 * Iterates over the provided array of environment strings (usually from
 * main's envp) and creates a linked list of t_env nodes. Each string is
 * split into key and value using the first '=' character. Nodes are
 * prepended to the list, so the resulting order is reversed compared
 * to the input array.
 *
 * @param envp Null-terminated array of strings in the format "KEY=VALUE".
 *
 * @return Pointer to the head of the newly created linked list, or NULL
 *         if memory allocation fails.
 *
 * @note The caller is responsible for freeing the list using free_env
 *       to avoid memory leaks.
 * @warning The list is built in reversed order compared to envp.
 */
t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	*new;

	head = NULL;
	while (*envp)
	{
		new = create_env_node(*envp);
		if (!new)
			return (NULL);
		new->next = head;
		head = new;
		envp++;
	}
	return (head);
}
