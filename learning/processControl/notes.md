# Process Control Notes

This file contains personal notes and experiments related to the `process control` system call.

## Process ownership

When a parent creates a child with `fork()`, it must `reap` the child after it exits.<br>
If the parent doesn’t call `wait()` (or `waitpid()`), the child becomes a zombie.
- `pid_t wait(int *status)` → waits for any child.
- `pid_t waitpid(pid_t pid, int *status, int options)` → waits for a specific child or checks without blocking (`WNOHANG`).
`status` encodes the exit information. Use macros:
- WIFEXITED(status) → child terminated normally
- WEXITSTATUS(status) → exit code
- WIFSIGNALED(status) → child killed by a signal
- WTERMSIG(status) → signal number

## Exit codes
A shell must track the child’s exit code (`$?` in bash).
This is retrieved with `WEXITSTATUS(status)` after `wait()`.

## Signals
Signals are asynchronous notifications sent to processes.

Examples:
- `SIGINT` (Ctrl+C)
- `SIGQUIT` (Ctrl+\\)
- `SIGKILL` (cannot be caught or ignored)


Functions:
- `kill(pid, sig)` — send a signal.
- `signal(sig, handler)` or `sigaction()` — set a handler.
