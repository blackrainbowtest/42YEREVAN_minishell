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

### Examples

- init: add base project structure
- feat: implement 'cd' built-in command
- fix: handle NULL input in parser
- refactor: optimize command execution loop
- docs: update README or other .md file with usage instructions
- style: fix indentation in parser.c

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

---
### Following these rules will keep the project clean, consistent, and easy to maintain.
---
