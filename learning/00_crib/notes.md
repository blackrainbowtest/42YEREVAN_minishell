# Cheat sheet for functions

## **All allowed functions in the minishell project**

- [readline](#readline)
- [rl_clear_history](#rl_clear_history)
- rl_on_new_line
- rl_replace_line
- rl_redisplay
- add_history
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
- Ошибки/нюансы:
	- После вызова история команд **полностью удаляется** из памяти.
	- Обычно используется при завершении программы, чтобы подчистить за собой.
---
