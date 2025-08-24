/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:23:31 by aramarak          #+#    #+#             */
/*   Updated: 2025/08/24 15:39:34 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell.h"

static int	is_blank(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (1);
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

static int	handle_builtins_or_exec(t_shell *sh, char **argv)
{
	if (!argv || !argv[0])
		return (0);
	if (strcmp(argv[0], "exit") == 0)
	{
		printf("exit\n");
		return (1); // сигнал выйти из REPL
	}
	if (strcmp(argv[0], "env") == 0)
	{
		ms_env_print(sh->env);
		return (0);
	}
	// временно — заглушка исполнителя:
	sh->last_status = execute_command(argv, sh);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	sh;
	char	*line;
	char	**args;
	int		should_exit;

	(void)argc;
	(void)argv;
	sh.env = ms_env_dup(envp);
	sh.last_status = 0;

	setup_signals();

	while (1)
	{
		line = read_prompt();
		if (!line)
			break ; // EOF (Ctrl+D)
		if (is_blank(line))
		{
			free(line);
			continue ;
		}
		args = parse_input(line);
		free(line);
		should_exit = handle_builtins_or_exec(&sh, args);
		free_argv(args);
		if (should_exit)
			break ;
	}
	printf("exit\n");
	ms_env_free(sh.env);
	return (0);
}
