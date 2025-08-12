# Execve Training Notes

This file contains personal notes and experiments related to the `execve()` system call.

## What does it do?

execve() replaces the current `process` with another.<br />

- The old code disappears.
- New code is loaded (for example, the `ls` program).
- The `process` continues to run under the same `PID`, but it is now a `different program`.

## Important rule

- The `execve()` call does not return if it is successful.
- If `execve()` returned, then an error occurred.
