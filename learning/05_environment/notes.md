# 05_environment

## Русская версия

### Что такое переменные окружения
- Переменные окружения — это пары `ключ=значение`, которые процесс получает от родителя.
- Они влияют на поведение программ.  
  Например:  
  - `PATH` — список директорий для поиска исполняемых файлов  
  - `HOME` — домашняя директория пользователя  
  - `USER` — имя пользователя  

### Где они хранятся
- В C: `char **environ` или как аргумент `main(int argc, char **argv, char **envp)`  
- Каждый элемент — строка вида `"NAME=value"`

### Использование в C
- `getenv("VAR")` → получить значение переменной  
- `setenv("VAR", "value", 1)` → установить/изменить  
- `unsetenv("VAR")` → удалить  

### Связь с execve
- `execve(path, argv, envp)` передаёт новое окружение процессу  
- Можно запускать программу с пустым окружением или с кастомным  

---

## English version

### What are environment variables
- Environment variables are `key=value` pairs inherited from the parent process.  
- They affect how programs run.  
  Examples:  
  - `PATH` — list of directories to search for executables  
  - `HOME` — user’s home directory  
  - `USER` — user name  

### Where they are stored
- In C: `char **environ` or as `main(int argc, char **argv, char **envp)`  
- Each entry is a string like `"NAME=value"`

### Usage in C
- `getenv("VAR")` → get variable value  
- `setenv("VAR", "value", 1)` → set/change  
- `unsetenv("VAR")` → remove  

### Relation with execve
- `execve(path, argv, envp)` passes a custom environment to the new process  
- You can launch a program with an empty or modified environment
