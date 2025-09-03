#include "minishell.h"

/**
 * @brief Implementation of the "echo" builtin command.
 *
 * Prints its arguments to the standard output. If the first argument
 * is "-n", the trailing newline is suppressed. Multiple arguments
 * are separated by a single space.
 *
 * @param args A NULL-terminated array of strings.
 *             - args[0]: the command name ("echo")
 *             - args[1..n]: the arguments to be printed
 *
 * @return Always returns 0.
 *
 * @note This function writes directly to stdout using printf() and write().
 */
int builtin_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	/* Check if the first argument is "-n" */
	if (args[1] && strcmp(args[1], "-n") == 0)
	{
		newline = 0;
		i = 2;
	}
	/* Print each argument separated by a space */
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	/* Print a newline if not suppressed */
	if (newline)
		write(1, "\n", 1);
	return (0);
}
