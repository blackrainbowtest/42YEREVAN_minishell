# Minishell

## 📖 Описание
Minishell — это учебный проект школы 42, в котором требуется написать собственный мини-интерпретатор команд (маленький bash).  
Проект помогает глубже понять процессы, файловые дескрипторы, работу сигналов, пайпы и редиректы.

## 📖 Description
Minishell is a school 42 project that requires writing your own mini-interpreter of commands (a small bash).
The project helps to better understand processes, file descriptors, signal operation, pipes and redirects.
---

## ✅ Разрешённые функции и библиотеки
## ✅ Allowed functions and libraries

### readline
- `readline`, `rl_clear_history`, `rl_on_new_line`,  
  `rl_replace_line`, `rl_redisplay`, `add_history`

### stdio.h
- `printf`

### stdlib.h
- `malloc`, `free`, `exit`

### unistd.h
- `write`, `access`, `read`, `close`, `fork`, `chdir`,  
  `dup`, `dup2`, `pipe`

### fcntl.h
- `open`, `unlink`

### sys/wait.h
- `wait`, `waitpid`, `wait3`, `wait4`

### signal.h
- `signal`, `sigaction`, `sigemptyset`, `sigaddset`, `kill`

### sys/stat.h
- `stat`, `lstat`, `fstat`

### dirent.h
- `opendir`, `readdir`, `closedir`

### string.h
- `strerror`

### stdio.h
- `perror`

### termios.h
- `isatty`, `ttyname`, `ttyslot`, `ioctl`,  
  `tcsetattr`, `tcgetattr`

### termcap (terminfo)
- `tgetent`, `tgetflag`, `tgetnum`, `tgetstr`, `tgoto`, `tputs`

---

## ⚙️ Builtins
- `echo` (с опцией / with option `-n`)
- `cd` (только путь / only way)
- `pwd`
- `export`
- `unset`
- `env`
- `exit`

## Project Structure

minishell/
├── subject/ # Project subject (PDF)
├── src/ # Source files
├── include/ # Header files
├── Makefile # Build instructions
├── README.md # This file
└── CONTRIBUTING.md # Contribution guide

## How to Build

```bash
make
./minishell
```

## Contribution

Please read [CONTRIBUTING.md](CONTRIBUTING.md) before making changes.

## Learning Branch

An additional branch `learning` exists for personal training.  
It contains experiments, notes, and test code related to minishell.  
These files are **not** part of the final 42 project.

## Tester

git clone https://github.com/LucasKuhn/minishell_tester.git
cd minishell_tester
./tester

bash -c "$(curl -fsSL https://raw.githubusercontent.com/zstenger93/42_minishell_tester/master/install.sh)"
``` :contentReference[oaicite:1]{index=1}  

## TODOS
- fix not updating the code inside the single quotes 
- fix exit codes
- fix <<-s
- check leaks
/bin/echo ""$?""