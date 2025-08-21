# 09_parsing

## Русская версия

**Парсинг в minishell** — это процесс преобразования введённой строки в структуру данных, с которой может работать программа.  
Этапы:

1. **Чтение ввода**  
   - Пользователь вводит строку (например: `echo "Hello World" > file.txt`).  

2. **Токенизация (лексический анализ)**  
   - Разбиение строки на "токены" (например: `echo`, `"Hello World"`, `>`, `file.txt`).  
   - Важно правильно обрабатывать кавычки (`"`, `'`), экранирование (`\`), и пробелы.  

3. **Построение структуры команд**  
   - Нужно определить, какие токены — это команда, какие — аргументы, какие — операторы (`>`, `<`, `|`).  

4. **Подготовка к выполнению**  
   - На этом шаге у тебя уже есть структура: список команд, каждая со своими аргументами и редиректами.  

Пример:  
``` c
echo "Hello World" > file.txt
```
Парсинг должен превратить это в:  
- Команда: `echo`  
- Аргументы: `["Hello World"]`  
- Редирект: `>` к файлу `file.txt`  

---

## English version

**Parsing in minishell** is the process of transforming the user’s input string into a data structure that the program can work with.  
Steps:

1. **Input reading**  
   - The user enters a command line (e.g. `echo "Hello World" > file.txt`).  

2. **Tokenization (lexical analysis)**  
   - Split the string into "tokens" (e.g. `echo`, `"Hello World"`, `>`, `file.txt`).  
   - Correctly handle quotes (`"`, `'`), escaping (`\`), and whitespace.  

3. **Building the command structure**  
   - Identify which tokens are commands, which are arguments, and which are operators (`>`, `<`, `|`).  

4. **Prepare for execution**  
   - At this step, you already have a structure: list of commands, each with its arguments and redirections.  

Example:  

``` c
echo "Hello World" > file.txt
```

Parsing should turn this into:  
- Command: `echo`  
- Arguments: `["Hello World"]`  
- Redirection: `>` to file `file.txt`  