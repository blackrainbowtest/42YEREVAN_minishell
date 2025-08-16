# Execve Training Notes

This file contains personal notes and experiments related to the `execve()` system call.

## What I learned today

### Function signature

- int `execve`(const char `*pathname`, char `*const argv[]`, char `*const envp[]`);

- `pathname` — path to the executable file (absolute or relative).
- `argv` — array of pointers to strings (command line arguments).
- `envp` — array of pointers to strings with environment variables.
---
1. `pathname`<br>
This is the path to the executable file you want to run.<br>
``` c
"/bin/ls"
"/usr/bin/env"
"./my_program"
```
`execve()` does not search for the program in `$PATH`- you need to pass the exact path.

---
2. `argv` <br>
This is an array of strings `(char* array)` that is passed to the new program as command line arguments.<br>
- `argv[0]` — usually the program name (by convention). It does not have to be a path — any name can be passed, but it is almost always either a file name or its path.
- `argv[1]`, `argv[2]`, ... — arguments.
- The last element is necessarily `NULL` — this is how the system understands where the array ends.
example:
```c
char *args[] = {"/bin/ls", "-l", "-a", NULL};
```
Inside the new program it will be:
```c
argv[0] = "/bin/ls"
argv[1] = "-l"
argv[2] = "-a"
argv[3] = NULL
```
Even if the program doesn't take any arguments, `argv[0]` must still be there (at least an empty string):
```c
char *args[] = {"/bin/ls", NULL};
```

---
3. envp
This is an array of strings of the form `NAME=value` representing environment variables.
```c
char *envp[] = {
    "USER=aramarak",
    "HOME=/home/aramarak",
    "PATH=/usr/bin:/bin",
    NULL
};
```
