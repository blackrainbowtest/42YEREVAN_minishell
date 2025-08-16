# Fork Training Notes

This file contains personal notes and experiments related to the `fork()` system call.

## What I learned today

- Basics of fork()
- How parent and child processes behave
- Examples and exercises

## What is this?

`fork()` - this is a `system call` that creates a `new process` (a copy of the current one)
- The process that called `fork()` is called the `parent process`.
- In the child process, `fork()` `returns 0`.
- If an error occurs (for example, not enough resources), it `returns -1` (and the `child process` is not created).

## What is important to understand?

- After fork() we have two processes running in parallel (or pseudo-parallel, depending on the scheduler).
- Memory is copied - each process has its own address space.
- The code is the same, but the variables in each process are independent.

## Mullocks when working with processes

### malloc before fork()

- The `parent` and `child` receive their own copies of memory (copy-on-write).
- If you don't call `free()` in the `parent`, there will be a leak in the `parent process`.
- If you don't call `free()` in the `child`, there will be no leak in terms of the long-lived program, because when the `child process` terminates, the `kernel` will free all the memory it had.

### malloc after fork()

- `Parent` and `child` allocate different pieces of memory in their processes.
- Each process must free its memory.
- If you don't call `free()` in the `parent`, there is a leak in the `parent`.
- If you don't call `free()` in the `child`, there will be a leak in the `child` (but again, after the `child process` terminates, the OS will return the memory, it's just a "dirty" habit).
