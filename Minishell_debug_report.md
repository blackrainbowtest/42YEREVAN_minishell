# 🐚 Minishell Debug Report

## 📅 Test Session
**Date:** 2025-10-21  
**Testers:** [____]  
**Commit tested:** `Checking for leaks and the functionality of basic builtins functions`  
**Environment:** Debian, cc, readline 8.1  

---

## 🧩 Summary
The main functions were tested, as well as the operation of built-in functions, for example, "su"

---

## 🪲 Bugs Found

### 1. ✔[Heredoc error] DONE
**Description:**  
Heredoc dont working.

**Steps to reproduce:**  
1. Command:  
   ```bash
   << ls
   ```
2. Command:  
   ```bash
   echo "hello" >> file | cat << file
   ```

### ✔2. [Exit error] DONE
**Description:**  
On exit didnt print exit.

**Steps to reproduce:**  
1. Command:  
   ```bash
   exit
   ```

### 3. [su error]
**Description:**  
Default command su not working.

**Steps to reproduce:**  
1. Command:  
   ```bash
   su -
   ```

### 4. ✔[doublicate error message] DONE
**Description:**  
Print doublicate error message on near unexpected token error.

**Steps to reproduce:**  
1. Command:  
   ```bash
   ls >> >> |
   ```
2. Command:  
   ```bash
   ls >>
   ```
3. Command:  
   ```bash
   ls >> >>
   ```

### ✔5. [No exit code on break] DONE
**Description:**  
Need exit with exit code on break.

**Steps to reproduce:**  
1. Command:  
   ```bash
   ^D
   ```

### 6. ✔[Leak error] DONE
**Description:**  
Catch leak when use echo with quote or double quote. read_quoted(token_quote.c:55)

**Steps to reproduce:**  
1. Command:  
   ```bash
   echo "a"
   ```
2. Command:  
   ```bash
   echo 'a'
   ```

### ✔8. [Invalid handling of special variable `_`] DONE

**Description:**  
The variable `_` is treated as a normal environment variable when declared or exported.  
In bash, `_` is a special shell variable and should not be manually set by `export` or `declare -x`.

**Steps to reproduce:**  
1. Run command:  
   ```bash
   declare -x _=""
   ```

### ✔9. [Invalid grep command] DONE

**Description:**
The variable is intercepted if there is text before it that satisfies the VALUE=KEY criteria; in other situations, the code works correctly.

**Steps to reproduce:**  
1. Run command:  
   ```bash
   env | grep "_="
   ```

27.10.2025

### ✔10. [Bad file descriptor] DONE

**Description:**
Get bad file descriptor when call (bug in child_process.c mumltiply call apply_redirections())

**Steps to reproduce:**
1. Run command:
   ```bash
   minishell$ cat << a | cat << b
   > d
   > f
   > a
   > d
   > b
   dup2: Bad file descriptor
   dup2: Bad file descriptor
   ```

### ✔11. [Bad SIGINT output] DONE

**Description:**
In heredoc SIGINT working double time, need disable it when we in heredock and restore it when exit

**Steps to reproduce:**
1. Run command:
   ```bash
   minishell$ << a << b
   > 
   minishell$ ^C
   ```

### ✔12. [Wrong exit code] DONE

**Description:**
Wrong exit code

**Steps to reproduce:**
1. Run command:
   ```bash
   minishell$ ls|<
   minishell: syntax error near unexpected token 'newline'
   minishell$ $?
   minishell: 0: command not found
   ```

### 13. [ENV update]

**Description:**
When changed data with export need update env too.

**Steps to reproduce:**
1. Run command:
   ```bash
   export TEST
   env
   ```

### 14. [Wrong error text]

**Description:**
When we havent access to open file (not enought permission) minishell return wrong error text

**Steps to reproduce:**
1. Run command:
   ```bash
   minishell$ chmod 000 a
   minishell$ echo a > a
   minishell: failed to open heredoc for `a'
   ```


### ✔15. [Wrong SIGINT code] DONE

**Description:**
When use SIGINT need update correct exit code

**Steps to reproduce:**
1. Run command:
   ```bash
   ^C
   ```

### ✔16. [Wrong error and exit code] DONE

**Description:**
When use solo pipe dont get error and exit code

**Steps to reproduce:**
1. Run command:
   ```bash
   minishell$ |  -> exit code check 
   ```
2. Run command:
   ```bash
   minishell$ unset PATH
   minishell$ ls | ls
   minishell$ 
   ```
3. Run command:
   ```bash
   minishell$ ls | a
   ```
### ✔17. [Makefile: libft not rebuilt] DONE
**Description:**  
The top-level Makefile did not trigger rebuilding libft when libft sources changed, so the project linked against an outdated libft.a.

**Steps to reproduce:**  
1. Modify any file under libft/ (e.g. libft/ft_strlen.c).  
2. Run `make` in the project root.  
   Previously libft was not rebuilt.

**Fix:**  
- Added in root Makefile: `LIBFT_SRCS = $(shell find $(LIBFT_DIR) -type f \( -name '*.c' -o -name '*.h' \))` and made `$(LIBFT)` depend on `$(LIBFT_SRCS)`, i.e. `$(LIBFT): $(LIBFT_SRCS)` so `make` runs `make -C libft` when libft sources change.  
- Updated `libft/Makefile` to print clear start/finish messages (e.g. "Compiling libft..." / "Finished compiling libft!").

**Status:** DONE

### ✔18. [Program accepts arguments] DONE
**Description:**  
Running `./minishell arg1 ...` started the shell although it must refuse any command-line arguments.

**Steps to reproduce:**  
1. Run:  
   ```bash
   ./minishell foo
   ```  
2. Observe the minishell prompt appears.

**Expected behavior:**  
Print an error to stderr and exit with a non‑zero status without entering the interactive shell.

**Fix implemented:**  
- Added a static helper `reject_args(int argc)` in `src/main.c` that checks `argc > 1`, prints the error string `MIN_EXIT_ERR` to stderr using `ft_putendl_fd`, and returns non‑zero.  
- `main()` now calls `reject_args(argc)` before any initialization and returns `1` if arguments were provided.  
- `ft_putendl_fd` is used instead of stdio functions (e.g. `fprintf`) to comply with project rules.  
- The argument check was extracted to a static function to keep `main` short (<= 26 lines).

**Files changed:**  
- src/main.c — added `static int reject_args(int argc)` and the call in `main`.

**Status:** DONE

### ✔19. [echo -n parsing] DONE
**Description:**  
Echo treated "-nnnn" and similar forms as normal arguments instead of recognizing them as repeated `-n` flags, printing the flag text instead of suppressing the trailing newline.

**Steps to reproduce:**  
1. Run:  
   ```bash
   echo -nnnn a
   ```  
   Previously output: `-nnnn a`  
   Expected (bash): `a` (no trailing newline)

**Fix implemented:**  
- `is_n_flag` now correctly recognizes `-n`, `-nn`, `-nnnn`, etc.  
- `builtin_echo` was changed to skip any number of consecutive `-n` flags (while loop) before printing arguments, so combinations like `echo -n -n a` and `echo -nnnn a` behave like bash.

**Files changed:**  
- src/builtins/echo.c — fixed `is_n_flag` usage and adjusted `builtin_echo` to iterate over multiple `-n` flags.

**Status:** DONE

