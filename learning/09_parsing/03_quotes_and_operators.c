#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static char	*ms_strdup(const char *s, int len)
{
	char	*copy;
	int		i;

	copy = malloc(len + 1);
	if (!copy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

static const char	*ms_token_quotes(const char *s, char **out)
{
	char	quote;
	const char	*start;

	quote = *s++;
	start = s;
	while (*s && *s != quote)
		s++;
	*out = ms_strdup(start, s - start);
	if (*s == quote)
		s++;
	return (s);
}

static const char	*ms_token_operator(const char *s, char **out)
{
	if ((s[0] == '>' && s[1] == '>') || (s[0] == '<' && s[1] == '<'))
	{
		*out = ms_strdup(s, 2);
		return (s + 2);
	}
	*out = ms_strdup(s, 1);
	return (s + 1);
}

static const char	*ms_token_word(const char *s, char **out)
{
	const char	*start;

	start = s;
	while (*s && !isspace((unsigned char)*s)
		&& *s != '>' && *s != '<' && *s != '|'
		&& *s != '\'' && *s != '"')
		s++;
	*out = ms_strdup(start, s - start);
	return (s);
}

char	**tokenize(const char *input)
{
	char	**tokens;
	int		size;
	const char	*p;
	char	*tok;

	tokens = NULL;
	size = 0;
	p = input;
	while (*p)
	{
		while (*p && isspace((unsigned char)*p))
			p++;
		if (!*p)
			break ;
		if (*p == '\'' || *p == '"')
			p = ms_token_quotes(p, &tok);
		else if (*p == '>' || *p == '<' || *p == '|')
			p = ms_token_operator(p, &tok);
		else
			p = ms_token_word(p, &tok);
		tokens = realloc(tokens, sizeof(char *) * (size + 2));
		tokens[size++] = tok;
		tokens[size] = NULL;
	}
	return (tokens);
}

int	main(void)
{
	char	*input;
	char	**tokens;
	int		i;

	input = "echo \"Hello World\" | grep World >> out.txt";
	tokens = tokenize(input);
	i = 0;
	while (tokens[i])
	{
		printf("token[%d] = [%s]\n", i, tokens[i]);
		free(tokens[i]);
		i++;
	}
	free(tokens);
	return (0);
}