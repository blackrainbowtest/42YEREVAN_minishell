# 04_io_redirection

## Русская версия
### Файловые дескрипторы (FD)
- `stdin` (0) — стандартный ввод
- `stdout` (1) — стандартный вывод
- `stderr` (2) — стандартный вывод ошибок

### dup и dup2
- `dup(oldfd)` — дублирует дескриптор
- `dup2(oldfd, newfd)` — перенаправляет `newfd` на `oldfd`
- Используется для редиректов: `stdout` → файл, `stdin` ← файл

### Перенаправления
- `>` — stdout → файл (перезапись)
- `>>` — stdout → файл (добавление)
- `<` — stdin ← файл

### Пайпы (pipe)
- `pipe(fd)` создаёт два дескриптора: `fd[0]` для чтения, `fd[1]` для записи
- Используется для передачи данных между процессами: `ls | wc -l`

## English version
### File descriptors (FD)
- `stdin` (0) — standard input
- `stdout` (1) — standard output
- `stderr` (2) — standard error

### dup and dup2
- `dup(oldfd)` — duplicates a descriptor
- `dup2(oldfd, newfd)` — redirects newfd to oldfd
- Used for redirection: `stdout` → file, `stdin` ← file

### Redirections
- `>` — stdout → file (overwrite)
- `>>` — stdout → file (append)
- `<` — stdin ← file

### Pipes
- `pipe(fd)` creates two descriptors: `fd[0]` read, `fd[1]` write
- Used to pass data between processes: `ls | wc -l`
