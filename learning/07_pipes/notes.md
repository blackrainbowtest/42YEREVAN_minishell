# 07_pipes

## Русская версия

### Что такое пайп (pipe)
- Пайп — это способ организации одностороннего канала между двумя процессами.
- Он позволяет одному процессу записывать данные, а другому читать их.
- Работает по принципу "пишущий → читающий".

### Как создать пайп
- `int fd[2];`
- `pipe(fd);`
- `fd[0]` — конец для чтения (read end)
- `fd[1]` — конец для записи (write end)

### Использование с fork
- Обычно пайп создаётся в родителе, затем после `fork()`:
  - Один процесс закрывает ненужный конец и использует `dup2` для перенаправления stdin/stdout.
  - Второй процесс делает то же самое, но с противоположным концом.
- Таким образом:  
  `ls` пишет в `fd[1]`, а `grep foo` читает из `fd[0]`.

### Важные функции
- `pipe(fd)` — создать пайп.
- `dup2(fd, new_fd)` — перенаправить стандартный ввод/вывод.
- `close(fd)` — обязательно закрывать неиспользуемые концы!
- `fork()` — нужен, чтобы создать два процесса, которые будут связаны пайпом.
- `execve()` — запускать команды внутри процессов.

### Пример: `ls | wc -l`
1. Создаём пайп.
2. Форкаем процесс.
3. Ребёнок → перенаправляет `stdout` в `fd[1]` и выполняет `ls`.
4. Родитель → перенаправляет `stdin` в `fd[0]` и выполняет `wc -l`.

---

## English version

### What is a pipe
- A pipe is a unidirectional communication channel between two processes.
- One process writes data, the other reads it.
- Works like: `writer → reader`.

### How to create a pipe
- `int fd[2];`
- `pipe(fd);`
- `fd[0]` — read end
- `fd[1]` — write end

### Using with fork
- The pipe is created in the parent before `fork()`.
- After forking:
  - The child closes unused ends, redirects stdout to `fd[1]`, and runs the first command.
  - The parent redirects stdin to `fd[0]`, and runs the second command.
- Example: `ls | grep foo` → `ls` writes, `grep` reads.

### Key functions
- `pipe(fd)` — create a pipe
- `dup2(fd, new_fd)` — redirect stdin/stdout
- `close(fd)` — always close unused ends
- `fork()` — create two processes
- `execve()` — run a command inside the process

### Example: `ls | wc -l`
1. Create pipe.
2. Fork process.
3. Child: redirect `stdout → fd[1]`, run `ls`.
4. Parent: redirect `stdin ← fd[0]`, run `wc -l`.
