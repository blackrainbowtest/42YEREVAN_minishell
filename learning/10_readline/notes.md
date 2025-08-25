# 10_readline

## Русская версия

**Функция readline()** — часть библиотеки GNU Readline, которая предоставляет удобный способ считывания строк из интерактивного терминала.
Она используется в `minishell`, чтобы пользователь мог вводить команды так же, как в обычном shell.

---
Основные возможности:

1. **Чтение строки**
	- `readline("prompt> ")` выводит приглашение **(prompt)** и ждёт ввода.
	- Возвращает указатель на введённую строку (динамически выделенную). 

2. **Редактирование ввода**

	- Пользователь может перемещать курсор, удалять символы, править строку прямо в терминале.

3. **История команд**

	- С помощью функции `add_history()` введённые строки сохраняются в историю.
	- Доступ к истории осуществляется стрелками ↑ и ↓.

4. **Автодополнение**
	- Readline поддерживает автодополнение (например, по клавише `Tab`).

---
Команда `readline()` является частью библиотеки `GNU Readline`, которая предоставляет функции для чтения строк с интерактивного терминала. Она широко используется в различных программных проектах для создания командных интерфейсов и обработки пользовательского ввода.

Функция `readline()` читает строку из стандартного вводного потока по умолчанию и возвращает указатель на эту строку. Она использует буферизацию, чтобы получить строку из потока, а затем возвращает указатель на эту строку после ввода пользователя.

Кроме того, функция `readline()` позволяет использовать строку при автодополнении, истории команд и других интерактивных функций. Она предоставляет возможность пользователю редактировать вводимый текст и перезапускать его, а также автоматически завершать команды по нажатию на клавишу `Tab`.

---
**Как подключить readline в проекте?**

1. Включить заголовки:
	``` c
	#include <readline/readline.h>
	#include <readline/history.h>
	```
2. Линковать библиотеку при компиляции:
	``` bash
	cc main.c -lreadline -o minishell
	```

**Полезные советы**
- Не забывай `free()` для каждой строки, которую вернула `readline()`
- Если хочешь отключить историю (например, при пустом вводе), просто не вызывай `add_history()`
- Чтобы история сохранялась между сессиями, можно использовать `write_history() / read_history()`, но для проекта 42 это обычно не требуется

---
[Ссылка на материал по `readline()`](https://linux.die.net/man/3/readline)

## English version

**The readline() function** is part of the GNU Readline library, which provides a convenient way to read lines from an interactive terminal.
It is used in `minishell` to allow the user to enter commands just as they would in a normal shell.

---
Key features:

1. **Reading a line**
- `readline("prompt> ")` displays the prompt **(prompt)** and waits for input.
- Returns a pointer to the entered line (dynamically allocated).

2. **Editing input**

- The user can move the cursor, delete characters, edit the line directly in the terminal.

3. **Command history**

- Using the `add_history()` function, entered lines are saved to the history.
- Access to the history is carried out by the ↑ and ↓ arrows.

4. **Autocompletion**
- Readline supports autocompletion (for example, by pressing the `Tab` key).

---
The `readline()` command is part of the `GNU Readline` library, which provides functions for reading lines from an interactive terminal. It is widely used in various software projects to create command interfaces and handle user input.

The `readline()` function reads a line from the standard input stream by default and returns a pointer to that line. It uses buffering to get the line from the stream, and then returns a pointer to that line after user input.

In addition, the `readline()` function allows the line to be used in autocompletion, command history, and other interactive features. It allows the user to edit and restart the entered text, as well as automatically complete commands by pressing the `Tab` key.

---
**How ​​to include readline in a project?**

1. Include headers:
``` c
#include <readline/readline.h>
#include <readline/history.h>
```
2. Link the library when compiling:
``` bash
cc main.c -lreadline -o minishell
```

**Helpful tips**
- Don't forget to `free()` for each line returned by `readline()`
- If you want to disable history (e.g. on empty input), just don't call `add_history()`
- To keep history between sessions, you can use `write_history()` / read_history()`, but for project 42 this is usually not needed

---
[Link to material on `readline()`](https://linux.die.net/man/3/readline)
