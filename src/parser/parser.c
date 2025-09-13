/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:27:13 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/11 20:27:26 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

static size_t	count_words(const char *s)
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 0;
	while (s && s[i])
	{
		while (s[i] && is_space(s[i]))
			i++;
		if (s[i])
		{
			words++;
			while (s[i] && !is_space(s[i]))
				i++;
		}
	}
	return (words);
}

static char	*sub_dup(const char *s, size_t start, size_t len)
{
	char	*out;
	size_t	i;

	out = (char *)malloc(len + 1);
	if (!out)
		return (NULL);
	i = 0;
	while (i < len)
	{
		out[i] = s[start + i];
		i++;
	}
	out[len] = '\0';
	return (out);
}

char	**parse_input(const char *line)
{
	size_t	i;
	size_t	k;
	size_t	start;
	size_t	words;
	char	**argv;

	i = 0;
	k = 0;
	if (!line)
		return (NULL);
	words = count_words(line);
	argv = (char **)malloc(sizeof(char *) * (words + 1));
	if (!argv)
		return (NULL);
	while (line[i])
	{
		while (line[i] && is_space(line[i]))
			i++;
		if (!line[i])
			break ;
		start = i;
		while (line[i] && !is_space(line[i]))
			i++;
		argv[k] = sub_dup(line, start, i - start);
		if (!argv[k++])
		{
			free_argv(argv);
			return (NULL);
		}
	}
	argv[k] = NULL;
	return (argv);
}

void	free_argv(char **argv)
{
	size_t	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(argv);
}
