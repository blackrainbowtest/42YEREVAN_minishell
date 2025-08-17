# 02_process_control

## Русская версия
### wait() и waitpid()
- `wait(&status)` — ждёт любого дочернего процесса.
- `waitpid(pid, &status, options)` — ждёт конкретного процесса.
- status хранит код завершения и информацию о сигнале:
  - `WIFEXITED(status)` — завершился нормально
  - `WEXITSTATUS(status)` — код возврата
  - `WIFSIGNALED(status)` — был убит сигналом
  - `WTERMSIG(status)` — номер сигнала

### Foreground и Background
- `Foreground` — процесс занимает терминал, родитель ждёт его.
- `Background` (с `&`) — процесс выполняется параллельно, родитель не блокируется.
- Родитель должен вызывать `waitpid()` для фоновых процессов, чтобы избежать зомби.

### Сигналы
- Сигналы — асинхронные уведомления для процессов.
- Примеры: `SIGINT` (Ctrl+C), `SIGQUIT` (Ctrl+\), `SIGKILL` (невозможно перехватить)
- `kill(pid, sig)` — отправить сигнал процессу
- `signal(sig, handler)` или `sigaction()` — обработка сигнала

## English version
### wait() and waitpid()
- `wait(&status)` — waits for any child process.
- `waitpid(pid, &status, options)` — waits for a specific child.
- status encodes exit code and signal info:
  - `WIFEXITED(status)` — exited normally
  - `WEXITSTATUS(status)` — exit code
  - `WIFSIGNALED(status)` — killed by a signal
  - `WTERMSIG(status)` — signal number

### Foreground and Background
- `Foreground` — occupies terminal, parent waits.
- `Background` (`&`) — runs in parallel, parent does not block.
- Parent should call `waitpid()` for background processes to avoid zombies.

### Signals
- Signals — asynchronous notifications for processes.
- Examples: `SIGINT` (Ctrl+C), `SIGQUIT` (Ctrl+\), `SIGKILL` (cannot be caught)
- `kill(pid, sig)` — send a signal
- `signal(sig, handler)` or `sigaction()` — handle signals
