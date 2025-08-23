#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **tokenize(const char *input) {
	char *copy = strdup(input);
	char *token = strtok(copy, " ");
	int size = 0;
	char **tokens = NULL;

	while (token) {
		tokens = realloc(tokens, sizeof(char*) * (size + 2));
		tokens[size++] = strdup(token);
		token = strtok(NULL, " ");
	}
	tokens[size] = NULL;
	free(copy);
	return tokens;
}

int main() {
	char input[] = "echo Hello World > file.txt";
	char **tokens = tokenize(input);

	for (int i = 0; tokens[i]; i++) {
		printf("token[%d] = %s\n", i, tokens[i]);
		free(tokens[i]);
	}
	free(tokens);
	return 0;
}
