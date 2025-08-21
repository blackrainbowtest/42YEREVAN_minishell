# 08_redirections

## Русская версия

### Что такое редиректы
- Редиректы позволяют перенаправлять стандартный ввод/вывод процесса.
- По умолчанию:
  - stdin (0) — клавиатура
  - stdout (1) — экран
  - stderr (2) — экран
- Редиректы меняют это поведение.

### Основные виды
- `>`  : перенаправить stdout в файл (перезаписать файл).
- `>>` : перенаправить stdout в файл (добавить в конец).
- `<`  : читать stdin из файла.
- `2>` : перенаправить stderr в файл.

### Как это работает
- Используется системный вызов `open()` для открытия файла.
- Затем `dup2(new_fd, STDOUT_FILENO)` или `dup2(new_fd, STDIN_FILENO)` перенаправляет стандартные потоки.
- После этого вызова `execve()` процесс пишет или читает не с экрана/клавиатуры, а из файла.

### Основные функции
- `open(filename, flags, mode)`  
  - `O_CREAT | O_WRONLY | O_TRUNC` — для `>`.
  - `O_CREAT | O_WRONLY | O_APPEND` — для `>>`.
  - `O_RDONLY` — для `<`.
- `dup2(fd, STDOUT_FILENO)` — перенаправить вывод в файл.
- `dup2(fd, STDIN_FILENO)` — перенаправить ввод из файла.
- `close(fd)` — закрыть файловый дескриптор.

---

## English version

### What are redirections
- Redirections allow changing the default input/output of a process.
- By default:
  - stdin (0) — keyboard
  - stdout (1) — screen
  - stderr (2) — screen
- Redirections change this behavior.

### Types
- `>`  : redirect stdout to a file (overwrite).
- `>>` : redirect stdout to a file (append).
- `<`  : redirect stdin from a file.
- `2>` : redirect stderr to a file.

### How it works
- Use `open()` to open/create a file.
- Then `dup2()` to replace stdin or stdout with the file descriptor.
- After that, `execve()` runs the program, and the program reads/writes from/to the file.

### Key functions
- `open(filename, flags, mode)`  
  - `O_CREAT | O_WRONLY | O_TRUNC` → for `>`.
  - `O_CREAT | O_WRONLY | O_APPEND` → for `>>`.
  - `O_RDONLY` → for `<`.
- `dup2(fd, STDOUT_FILENO)` → redirect output to file.
- `dup2(fd, STDIN_FILENO)` → redirect input from file.
- `close(fd)` → always close the file descriptor.
