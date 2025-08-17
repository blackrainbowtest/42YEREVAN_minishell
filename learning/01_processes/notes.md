# 01_processes

## Русская версия
### Основы процессов
- Процесс — это выполняемая программа в системе.
- Каждый процесс имеет уникальный `PID` (идентификатор процесса) и `PPID` (идентификатор родителя).
- При `fork()` создаётся копия процесса:
  - Копируются память, стек, регистры.
  - `PID` дочернего процесса уникален.

### fork()
- Системный вызов для создания нового процесса.
- Возвращает:
  - `0` → дочерний процесс
  - `>0` → родительский процесс (`PID` ребёнка)
  - `<0` → ошибка

### malloc() и fork()
- Если `malloc` вызывается **до fork()**, память копируется при создании дочернего процесса.
- Если `malloc` вызывается **после fork()** — память уже только у процесса, который её выделил.
- Всегда освобождать память (`free`) в каждом процессе.

### zомби-процессы
- Возникают, если дочерний процесс завершился, но родитель не вызвал `wait()` или `waitpid()`.
- `PID` остаётся в таблице процессов, пока родитель не прочитает статус.

## English version
### Basics of Processes
- A process is a running program in the system.
- Each process has a unique `PID` and `PPID` (parent PID).
- `fork()` creates a copy of the process:
  - Memory, stack, registers are copied.
  - Child `PID` is unique.

### fork()
- System call to create a new process.
- Returns:
  - `0` → child process
  - `>0` → parent process (PID of child)
  - `<0` → error

### malloc() and fork()
- `malloc` before fork → memory is copied to child process.
- `malloc` after fork → memory exists only in the process that allocated it.
- Always free allocated memory in each process.

### Zombie processes
- Happen when child terminates but parent does not call `wait()`/`waitpid()`.
- `PID` remains in process table until parent reads status.
