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

### 1. [Heredoc error]
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

### 4. [doublicate error message]
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

### ✔5. [No exit code on break]
**Description:**  
Need exit with exit code on break.

**Steps to reproduce:**  
1. Command:  
   ```bash
   ^D
   ```

### 6. [Leak error]
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

### 8. [Invalid handling of special variable `_`]

**Description:**  
The variable `_` is treated as a normal environment variable when declared or exported.  
In bash, `_` is a special shell variable and should not be manually set by `export` or `declare -x`.

**Steps to reproduce:**  
1. Run command:  
   ```bash
   declare -x _=""
   ```

### 9. [Invalid grep command]

**Description:**
The extern command get wrong arguments maybe NULL

**Steps to reproduce:**  
1. Run command:  
   ```bash
   env | grep "_="
   ```