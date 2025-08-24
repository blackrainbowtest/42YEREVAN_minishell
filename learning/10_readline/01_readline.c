#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char* input;

    // Инициализация readline
    rl_bind_key('\t', rl_complete); // Включение автодополнения по Tab

    while (1) {
        input = readline("Ваша команда: "); // Вывод строки-приглашения и чтение ввода

        if (!input) {
            break;
        }

        if (strcmp(input, "exit") == 0) {
            free(input);
            break;
        }

        // Ваш код обработки введенной команды
        printf("Вы ввели: %s\n", input);

        add_history(input); // Добавление введенной команды в историю

        free(input);
    }

    return 0;
}
