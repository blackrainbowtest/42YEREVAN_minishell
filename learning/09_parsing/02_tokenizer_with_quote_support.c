#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *get_token(const char **str) {
    const char *s = *str;
    char *token = malloc(1024);
    int pos = 0;
    char quote = 0;

    while (*s && isspace((unsigned char)*s))
        s++;

    if (!*s) {
        *str = s;
        free(token);
        return NULL;
    }

    if (*s == '"' || *s == '\'') {
        quote = *s++;
        while (*s && *s != quote) {
            token[pos++] = *s++;
        }
        if (*s == quote) s++;
    } else {
        while (*s && !isspace((unsigned char)*s) && *s != '"' && *s != '\'') {
            token[pos++] = *s++;
        }
    }

    token[pos] = '\0';
    *str = s;
    return token;
}

char **tokenize(const char *input) {
    const char *p = input;
    char **tokens = NULL;
    int size = 0;

    while (1) {
        char *token = get_token(&p);
        if (!token) break;
        tokens = realloc(tokens, sizeof(char*) * (size + 2));
        tokens[size++] = token;
        tokens[size] = NULL;
    }
    return tokens;
}

int main() {
    char input[] = "echo \"Hello World\" 'minishell test' > file.txt";
    char **tokens = tokenize(input);

    for (int i = 0; tokens[i]; i++) {
        printf("token[%d] = [%s]\n", i, tokens[i]);
        free(tokens[i]);
    }
    free(tokens);
    return 0;
}
