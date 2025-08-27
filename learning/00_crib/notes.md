# Cheat sheet for functions

## **All allowed functions in the minishell project**

- [readline](#readline)
- [rl_clear_history](#rl_clear_history)
- [rl_on_new_line](#rl_on_new_line)
- [rl_replace_line](#rl_replace_line)
- [rl_redisplay](#rl_redisplay)
- [add_history](#add_history)
- printf
- malloc
- free
- write
- access
- open
- read
- close
- fork
- wait
- waitpid
- wait3
- wait4
- signal
- sigaction
- sigemptyset
- sigaddset
- kill
- exit
- getcwd
- chdir
- stat
- lstat
- fstat
- unlink
- execve
- dup
- dup2
- pipe
- opendir
- readdir
- closedir
- strerror
- perror
- isatty
- ttyname
- ttyslot
- ioctl
- getenv
- tcsetattr
- tcgetattr
- tgetent
- tgetflag
- tgetnum
- tgetstr
- tgoto
- tputs

## 📘 Description of functions
Below are the breakdowns of each function: its purpose, arguments and usage examples.
---

### **readline**
- **Назначение:** читает строку с терминала, отображает приглашение `(prompt)` и ждёт ввода. Поддерживает редактирование строки (стрелки, backspace и т.п.).
- Прототип:
	``` c
	char *readline(const char *prompt);
	```
- Аргументы:
	- `prompt` — строка, которая выводится перед вводом (например, "minishell$ ").

- Возвращает:
	- Указатель на введённую строку (динамически выделенную, нужно освобождать через `free`).
	- `NULL`, если достигнут `EOF` (например, `Ctrl+D`).
	
- Ошибки/нюансы:
	- ⚠️ Необходимо проверять `NULL`.
	- 🧹 Память всегда нужно **освобождать**.
---
### **rl_clear_history**
- **Назначение:** очищает всю историю, собранную readline/add_history.
- Прототип:
	``` c
	void rl_clear_history(void);
	```
- Аргументы:
	- Нет
- Возвращает:
	- Ничего
- Нюансы:
	- После вызова история команд **полностью удаляется** из памяти.
	- Обычно используется при завершении программы, чтобы подчистить за собой.
---
### **rl_on_new_line**
- **Назначение:** сообщает библиотеке `readline`, что курсор сейчас находится на новой строке. Используется перед обновлением или перерисовкой строки.
- Прототип:
	``` c
	void rl_on_new_line(void);
	```
- Аргументы:
	- Нет
- Возвращает:
	- Ничего
- Нюансы:
	- Часто вызывается перед [rl_redisplay](#rl_redisplay), чтобы корректно обновить ввод пользователя.
---
### **rl_replace_line**
- **Назначение:** заменяет текущую строку ввода на новую строку, не дожидаясь `Enter`.
- Прототип:
	``` c
	void rl_replace_line(const char *text, int clear_undo);
	```
- Аргументы:
	- `text` — новая строка для ввода.
	- `clear_undo` — если ненулевой, очищает буфер undo (отмену предыдущих изменений).
- Возвращает:
	- Ничего
- Нюансы:
	- Используется, чтобы программно подставить строку в `readline`.
	- После вызова обычно делают [rl_redisplay()](#rl_redisplay), чтобы обновить отображение.
---
### **rl_redisplay**
- **Назначение:** перерисовывает текущую строку ввода на экране. Используется после программного изменения строки ([rl_replace_line](#rl_replace_line)) или когда нужно обновить отображение.
- Прототип:
	``` c
	void rl_redisplay(void);
	```
- Аргументы:
	- Нет
- Возвращает:
	- Ничего
- Нюансы:
	- Часто используется вместе с [rl_on_new_line()](#rl_on_new_line) и [rl_replace_line()](#rl_replace_line).
	- Не меняет содержимое строки, только визуально обновляет её.
---
### **add_history**
- **Назначение:** добавляет строку в историю команд readline.
- Прототип:
	``` c
	void add_history(const char *line);
	```
- Аргументы:
	- `line` — строка, которую нужно сохранить в истории.
- Возвращает:
	- Ничего
- Нюансы:
	- Не добавляет `NULL` или пустые строки (`""`).
	- История хранится в памяти до завершения программы или вызова [rl_clear_history()](#rl_clear_history).
	- Позволяет пользователю потом переключаться по истории стрелками `↑`/`↓`.