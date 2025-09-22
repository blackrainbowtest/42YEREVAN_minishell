/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 12:01:26 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/20 20:55:10 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void expand_tokens(t_token *tokens, t_env *env)
{
    t_token *tok;
    char    *expanded;

    tok = tokens;
    while (tok)
    {
        if (tok->type == T_SQUOTE)
        {
        }
        else if (tok->type == T_DQUOTE || tok->type == T_WORD || tok->type == T_VAR)
        {
            expanded = expand_string(tok->value, env);
            if (expanded)
            {
                free(tok->value);
                tok->value = expanded;
            }
        }
        tok = tok->next;
    }
}

char *expand_string(const char *str, t_env *env)
{
    size_t  i = 0;
    char    *result = ft_strdup("");
    char    *tmp;

    while (str[i])
    {
        if (str[i] == '$')
        {
            size_t start = ++i;
            if (str[i] == '?')
            {
                tmp = ft_itoa(last_status(0, 0));
                i++;
            }
            else
            {
                while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
                    i++;
                char *name = ft_substr(str, start, i - start);
                char *val = ft_getenv(env, name);
                free(name);
                tmp = val ? ft_strdup(val) : ft_strdup("");
            }
            char *joined = ft_strjoin(result, tmp);
            free(result);
            free(tmp);
            result = joined;
        }
        else
        {
            char buf[2] = {str[i], 0};
            char *joined = ft_strjoin(result, buf);
            free(result);
            result = joined;
            i++;
        }
    }
    return (result);
}
