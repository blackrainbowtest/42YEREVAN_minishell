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

**
minishell$ su -
Password: 
minishell: lslslslsl: command not found
minishell: afsd: command not found
minishell: adsf: command not found
**

**
minishell$ << "$USER"
> $USER
> aramarak
minishell$ 
**

https://github.com/zstenger93/42_minishell_tester show this





minishell$ cat a
cat: a: Permission denied
minishell$ $?
minishell: 1: command not found

minishell$ < a

