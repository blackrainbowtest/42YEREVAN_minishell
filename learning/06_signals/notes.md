# 06_signals

## Русская версия

### Что такое сигнал
- Сигнал — это способ ОС сообщить процессу о событии.
- Сигналы можно сравнить с "прерываниями" на уровне процессов.
- Примеры сигналов:
  - `SIGINT` (2) — прерывание (`Ctrl+C`)
  - `SIGQUIT` (3) — выход (`Ctrl+\`)
  - `SIGTERM` (15) — завершение
  - `SIGKILL` (9) — немедленное убийство (не может быть перехвачен)
  - `SIGCHLD` — отправляется родителю при завершении дочернего процесса

### Работа с сигналами
- `kill(pid, sig)` — послать сигнал процессу
- `signal(sig, handler)` — установить обработчик сигнала
- `sigaction` — более надёжная и современная версия `signal`
- `raise(sig)` — послать сигнал самому себе
- `pause()` — процесс "засыпает", пока не получит сигнал

### Почему это важно для minishell
- `Ctrl+C` должно останавливать ввод и показывать новую строку, но не завершать шелл.
- `Ctrl+D` (EOF) должен завершать программу, если строка пустая.
- `Ctrl+\` обычно игнорируется (или выводит `Quit (core dumped)` в bash).

---

## English version

### What is a signal
- A signal is a way for the OS to notify a process about an event.
- They are like "software interrupts" for processes.
- Common signals:
  - `SIGINT` (2) — interrupt (`Ctrl+C`)
  - `SIGQUIT` (3) — quit (`Ctrl+\`)
  - `SIGTERM` (15) — termination
  - `SIGKILL` (9) — kill immediately (cannot be caught)
  - `SIGCHLD` — sent to parent when a child process terminates

### Working with signals
- `kill(pid, sig)` — send a signal to a process
- `signal(sig, handler)` — set a signal handler
- `sigaction` — safer and more flexible than `signal`
- `raise(sig)` — send a signal to yourself
- `pause()` — wait until a signal is received

### Why it matters for minishell
- `Ctrl+C` should stop current input and print a new prompt, without exiting the shell.
- `Ctrl+D` (EOF) should exit if the line is empty.
- `Ctrl+\` is usually ignored (or prints `Quit (core dumped)` in bash).
