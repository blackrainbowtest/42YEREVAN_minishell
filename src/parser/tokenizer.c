/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:27:13 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/11 20:27:26 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Creates a new token with a given string value and type.
 *
 * This function allocates memory for a new `t_token` structure, duplicates
 * the provided string `str` into the token's `value` field, and sets its
 * type and next pointer. It is typically used when constructing or
 * extending a linked list of tokens. The caller is responsible for freeing
 * the returned token (and its value) when no longer needed.
 *
 * @param str The string to store in the token's `value`. Must not be NULL.
 * @param type The type of the token, as defined by the `t_toktype` enum.
 *
 * @return A pointer to the newly created token. Returns NULL if memory
 *         allocation fails either for the token itself or for the duplicated
 *         string.
 *
 * @note The function uses `ft_strdup` to copy the string, so the caller
 *       can safely modify or free the original `str` after calling.
 * @warning Always check the return value for NULL to avoid dereferencing
 *          a failed allocation.
 */
static t_token	*new_token(const char *str, t_toktype type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(str);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->type = type;
	token->next = NULL;
	return (token);
}

/**
 * @brief Adds a token to the end of a linked list of tokens.
 *
 * This function appends the provided `new` token to the end of the linked
 * list pointed to by `lst`. If the list is empty (`*lst` is NULL), `new`
 * becomes the first element. It is commonly used when building a list of
 * tokens incrementally.
 *
 * @param lst Pointer to the pointer of the first token in the list.
 *        Can be NULL, in which case the function does nothing.
 * @param new Pointer to the token to be added. Must not be NULL.
 *
 * @return This function does not return a value.
 *
 * @note After calling this function, the `new` token is linked to the list
 *       and should not be freed separately until the entire list is freed.
 * @warning Do not pass a token that is already part of another list, as
 *          this will corrupt the linked structure.
 */
static void	token_add_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

static void	token_add_last(t_token **lst, char *str)
{
	t_token	*tmp;
	char	*new_value;

	if (!lst || !*lst)
		return ;
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	new_value = ft_strjoin(tmp->value, str);
	free(tmp->value);
	tmp->value = new_value;
}

t_token	*get_last_token(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/**
 * @brief Extracts a substring enclosed in quotes from a given line.
 *
 * This function reads characters from `line` starting at index `*i`, expecting
 * a quoted string (either single `'` or double `"` quotes). It allocates a new
 * string containing the content between the quotes and returns it. The index
 * `*i` is updated to point just after the closing quote. If the closing quote
 * is not found or memory allocation fails, the function returns NULL.
 *
 * @param line The input string containing the quoted segment.
 * @param i Pointer to the current index in `line`. On return, `*i` is updated
 *          to the character immediately after the closing quote.
 *
 * @return A newly allocated string containing the quoted content. Returns
 *         NULL if the closing quote is missing or memory allocation fails.
 *
 * @note The caller is responsible for freeing the returned string.
 * @warning Ensure that `*i` initially points to a quote character in `line`.
 * @bug None known.
 */
static t_token *read_quoted(const char *line, size_t *i)
{
	char		quote;
	size_t		start;
	t_toktype	type;
	char		*substr;

	quote = line[*i];
	if (quote == '\'') 
		type = T_SQUOTE;
	else
		type = T_DQUOTE;
	start = ++(*i);
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (!line[*i])
		return (NULL);
	substr = ft_substr(line, start, *i - start);
	(*i)++;
	if (!substr)
		return (NULL);
	return (new_token(substr, type));
}

/**
 * @brief Short description of the function (1 sentence).
 *
 * More detailed explanation if needed. Describe what the function does,
 * how it works, and when it should be used. Mention side effects if any
 * (e.g., modifies global state, writes to stdout).
 *
 * @param param1 Description of the first parameter.
 * @param param2 Description of the second parameter.
 *        (continue for all parameters)
 *
 * @return Description of the return value. If the function always
 *         returns the same value (e.g., 0), state that clearly.
 *
 * @note (optional) Additional notes about usage or constraints.
 * @warning (optional) Mention if function has limitations or risks.
 * @bug (optional) Known bugs, if any.
 * @todo (optional) Things planned to improve this function.
 */
t_token	*tokenize(const char *line)
{
	t_token		*head;
	size_t		i;
	size_t		start;
	t_token		*qtoken;
	int			quote_start;
	char		*token;
	t_token		*last;

	head = NULL;
	i = 0;
	while (line[i])
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (!line[i])
			break ;
		if (line[i] == '\'' || line[i] == '"')
		{
			quote_start = i;
			qtoken = read_quoted(line, &i);
			if (!qtoken)
				return (free_tokens(head), NULL);
			last = get_last_token(head);
			if (last
				&& (last->type == T_WORD || last->type == T_DQUOTE)
				&& line[quote_start - 1] != ' '
				&& line[quote_start - 1] != '\t')
			{
				token_add_last(&head, qtoken->value);
				free(qtoken->value);
				free(qtoken);
			}
			else
				token_add_back(&head, qtoken);
		}
		else if (line[i] == '|')
		{
			token_add_back(&head, new_token("|", T_PIPE));
			i++;
		}
		else if (line[i] == '<' || line[i] == '>')
		{
			if (line[i] == '<' && line[i + 1] == '<')
			{
				token_add_back(&head, new_token("<<", T_HEREDOC));
				i += 2;
			}
			else if (line[i] == '>' && line[i + 1] == '>')
			{
				token_add_back(&head, new_token(">>", T_REDIR_APPEND));
				i += 2;
			}
			else if (line[i] == '<')
			{
				token_add_back(&head, new_token("<", T_REDIR_IN));
				i++;
			}
			else
			{
				token_add_back(&head, new_token(">", T_REDIR_OUT));
				i++;
			}
		}
		else if (line[i] == '$')
		{
			start = i++;
			if (line[i] == '?')
				i++;
			else
			{
				while (line[i] && ((line[i] >= 'A' && line[i] <= 'Z')
						|| (line[i] >= 'a' && line[i] <= 'z')
						|| (line[i] >= '0' && line[i] <= '9')
						|| line[i] == '_'))
					i++;
			}
			token = malloc(i - start + 1);
			if (!token)
				return (free_tokens(head), NULL);
			ft_strlcpy(token, line + start, i - start + 1);
			token_add_back(&head, new_token(token, T_VAR));
			free(token);
		}
		else
		{
			start = i;
			while (line[i] && line[i] != ' ' && line[i] != '\t'
				&& line[i] != '\'' && line[i] != '"'
				&& line[i] != '|' && line[i] != '<' && line[i] != '>'
				&& line[i] != '$')
				i++;
			token = malloc(i - start + 1);
			if (!token)
				return (free_tokens(head), NULL);
			ft_strlcpy(token, line + start, i - start + 1);
			token_add_back(&head, new_token(token, T_WORD));
			free(token);
		}
	}
	return (head);
}

/**
 * @brief Short description of the function (1 sentence).
 *
 * More detailed explanation if needed. Describe what the function does,
 * how it works, and when it should be used. Mention side effects if any
 * (e.g., modifies global state, writes to stdout).
 *
 * @param param1 Description of the first parameter.
 * @param param2 Description of the second parameter.
 *        (continue for all parameters)
 *
 * @return Description of the return value. If the function always
 *         returns the same value (e.g., 0), state that clearly.
 *
 * @note (optional) Additional notes about usage or constraints.
 * @warning (optional) Mention if function has limitations or risks.
 * @bug (optional) Known bugs, if any.
 * @todo (optional) Things planned to improve this function.
 */
void	free_tokens(t_token *lst)
{
	t_token	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->value);
		lst->value = NULL;
		free(lst);
		lst = tmp;
	}
}
