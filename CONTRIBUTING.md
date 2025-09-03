# Contribution Guide for Minishell

## Commit Language
- All commit messages **must be in English**.
- Keep them short, clear, and descriptive (max ~72 characters for the subject line).
- Use lowercase for the prefix.

## Commit Format

``` bash
<prefix>: short description
```

### Allowed Prefixes

- `init:` — initial project setup or structure.
- `feat:` — add new functionality.
- `fix:` — fix a bug.
- `refactor:` — change code without changing its behavior.
- `docs:` — documentation changes.
- `style:` — code style changes (formatting, indentation, etc.) with no logic changes.
- `test:` — add or modify tests.
- `build:` — changes affecting build system or external dependencies.
- `chore:` — other tasks like cleanup, maintenance, tooling, or non-functional changes.

### Examples

- init: add base project structure
- feat: implement 'cd' built-in command
- fix: handle NULL input in parser
- refactor: optimize command execution loop
- docs: update README or other .md file with usage instructions
- style: fix indentation in parser.c
- chore: add learning/fork notes and directory for training

### Working with Branches

- Do not commit directly to main.
- Create a new branch for each feature or fix:
``` bash
git checkout -b feat/<feature-name>
```
- Push your branch to GitHub:
``` bash
git push origin feat/<feature-name>
```

### Pull Requests

- Always create a Pull Request to merge your branch into main.
- Another team member should review and approve your PR before merging.
- Ensure your branch is up-to-date with main before merging:
``` bash
git pull origin main
```

### Function templates

Generic Doxygen template for functions in minishell. 

``` c
/**
 * @brief Short description of the function (1 sentence).
 *
 * More detailed explanation if needed. Describe what the function does,
 * how it works, and when it should be used. Mention side effects if any
 * (e.g., modifies global state, writes to stdout).
 *
 * @param param1 Description of the first parameter.
 * @param param2 Description of the second parameter.
 *        (continue for all parameters)
 *
 * @return Description of the return value. If the function always
 *         returns the same value (e.g., 0), state that clearly.
 *
 * @note (optional) Additional notes about usage or constraints.
 * @warning (optional) Mention if function has limitations or risks.
 * @bug (optional) Known bugs, if any.
 * @todo (optional) Things planned to improve this function.
 */
```

---
### Following these rules will keep the project clean, consistent, and easy to maintain.
---
