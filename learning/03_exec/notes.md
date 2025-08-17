# 03_exec

## Русская версия
### Основы exec
- Функции `exec` заменяют текущий процесс новой программой.
- `PID` остаётся тот же, процесс не создаётся заново.
- Старый код и память стираются.
- Если `exec` успешен, код после вызова **не выполняется**.

### Варианты
- `execl(path, arg0, arg1, ..., NULL)` — аргументы списком
- `execv(path, argv)` — аргументы массивом
- `execle(path, arg0, ..., NULL, envp)` — с окружением
- `execve(path, argv, envp)` — базовый системный вызов

### Аргументы execve
- `pathname` — путь к бинарному файлу
- `argv` — массив аргументов (argv[0] — имя программы)
- `envp` — массив переменных окружения

### Использование после fork()
- Родитель остаётся оболочкой.
- Дочерний процесс вызывает `exec` для запуска команды.
- Код после `exec` выполняется только при ошибке.

## English version
### Basics of exec
- `exec` functions replace current process with a new program.
- `PID` stays the same; no new process is created.
- Old code and memory are replaced.
- If `exec` succeeds, code after call does **not run**.

### Variants
- `execl(path, arg0, arg1, ..., NULL)` — arguments as list
- `execv(path, argv)` — arguments as array
- `execle(path, arg0, ..., NULL, envp)` — with environment
- `execve(path, argv, envp)` — low-level syscall

### execve arguments
- `pathname` — path to executable
- `argv` — array of arguments (argv[0] = program name)
- `envp` — array of environment variables

### Using after fork()
- Parent stays as shell.
- Child calls `exec` to run command.
- Code after `exec` runs only if error occurs.
