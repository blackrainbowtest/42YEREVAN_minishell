/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:20:18 by aramarak          #+#    #+#             */
/*   Updated: 2025/10/01 01:08:43 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Handles the SIGINT signal (Ctrl+C) in the shell.
 *
 * This function is registered as a signal handler for SIGINT.
 * When the user presses Ctrl+C, it moves the cursor to a new line,
 * clears the current input line, and redisplays the prompt without exiting
 * the shell. It does not terminate the program.
 *
 * @param sig The signal number (ignored in this handler).
 *
 * @note This handler is designed to work with GNU readline.
 * @warning Modifies the readline state; should only be used in the main shell
 *          input loop.
 */
static void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		if (!in_child_process(0, 0))
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

void	signal_ctlc_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		close(STDIN_FILENO);
		write(STDERR_FILENO, "\n", 1);
	}
}

/**
 * @brief Configures signal handling for the shell.
 *
 * This function sets up custom signal handlers for the shell. It registers
 * `sigint_handler` for SIGINT (Ctrl+C) to allow the shell to handle
 * interrupts gracefully without exiting. It ignores the SIGQUIT signal
 * (Ctrl+\) to prevent the shell from quitting unexpectedly.
 *
 * @return This function does not return a value.
 *
 * @note Should be called once during shell initialization, before the main
 *       input loop starts.
 * @warning Modifies the process's global signal handlers; calling this
 *          multiple times may overwrite previous handlers.
 */
void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
