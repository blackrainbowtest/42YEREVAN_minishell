root@DESKTOP-OCTCNHU:~/42YEREVAN_minishell# norminette 
src/utils.c: OK!
src/signals.c: OK!
src/main.c: Error!
Error: WRONG_SCOPE_COMMENT  (line:  34, col:   5):      Comment is invalid in this scope
Error: WRONG_SCOPE_VAR      (line:  37, col:   1):      Variable declared in incorrect scope
Error: DECL_ASSIGN_LINE     (line:  37, col:  18):      Declaration and assignation on a single line
Error: TOO_MANY_LINES       (line:  51, col:   1):      Function has more than 25 lines
src/prompt.c: OK!
src/cleaner.c: Error!
Error: BRACE_SHOULD_EOL     (line:  21, col:   1):      Expected newline after brace
src/path.c: OK!
src/storage.c: OK!
src/executors/executor_utils.c: OK!
src/executors/child_process.c: Error!
Error: WRONG_SCOPE_COMMENT  (line:  74, col:   5):      Comment is invalid in this scope
Error: WRONG_SCOPE_VAR      (line:  77, col:   1):      Variable declared in incorrect scope
Error: DECL_ASSIGN_LINE     (line:  77, col:  18):      Declaration and assignation on a single line
Error: TOO_MANY_LINES       (line:  91, col:   1):      Function has more than 25 lines
Error: EMPTY_LINE_EOF       (line: 101, col:   1):      Empty line at end of file
src/executors/execute_pipeline.c: Error!
Error: ASSIGN_IN_CONTROL    (line:  23, col:  22):      Assignment in control structure
Error: TERNARY_FBIDDEN      (line:  57, col:  23):      Ternaries are forbidden
src/executors/executor.c: OK!
src/builtins/run_builtin.c: OK!
src/builtins/pwd.c: OK!
src/builtins/echo.c: OK!
src/builtins/export.c: OK!
src/builtins/cd.c: OK!
src/builtins/export_utils.c: OK!
src/builtins/env.c: OK!
src/builtins/unset.c: OK!
src/builtins/exit.c: OK!
src/debug/debug_tokens.c: OK!
src/debug/debug_parser.c: OK!
src/redirections/utils_redir.c: OK!
src/redirections/heredoc_utils.c: OK!
src/redirections/apply_redirections.c: OK!
src/redirections/heredoc_signals.c: OK!
src/redirections/open_files.c: OK!
src/parser/parse_tokens_process.c: OK!
src/parser/token_list.c: OK!
src/parser/parse_tokens_utils.c: OK!
src/parser/token_free.c: OK!
src/parser/parser_line.c: OK!
src/parser/parser_redirs.c: OK!
src/parser/token_helper_operator.c: OK!
src/parser/parse_utils.c: OK!
src/parser/token_helper.c: OK!
src/parser/parser_args.c: OK!
src/parser/expand_utils.c: OK!
src/parser/expand_tokens_utils.c: OK!
src/parser/parser_words.c: OK!
src/parser/token_quote.c: OK!
src/parser/parse_tokens.c: OK!
src/parser/expand_tokens.c: OK!
src/parser/tokenizer.c: OK!
src/status/status.c: OK!
src/env/env_local.c: OK!
src/env/env_local_utils.c: OK!
src/env/env_utils.c: OK!
src/env/env_create_utils.c: OK!
src/env/env.c: OK!
libft/ft_strlcat.c: OK!
libft/ft_putnbr_fd.c: OK!
libft/ft_isprint.c: OK!
libft/ft_lstsize.c: OK!
libft/ft_strncmp.c: OK!
libft/ft_putchar_fd.c: OK!
libft/ft_lstiter.c: OK!
libft/ft_calloc.c: OK!
libft/ft_putendl_fd.c: OK!
libft/ft_isalpha.c: OK!
libft/ft_tolower.c: OK!
libft/ft_lstlast.c: OK!
libft/ft_split.c: OK!
libft/ft_strtrim.c: OK!
libft/ft_lstclear.c: OK!
libft/ft_strjoin.c: OK!
libft/ft_free_split.c: OK!
libft/ft_lstmap.c: OK!
libft/ft_itoa.c: OK!
libft/ft_strlcpy.c: OK!
libft/ft_memcpy.c: OK!
libft/ft_strrchr.c: OK!
libft/ft_lstadd_front.c: OK!
libft/ft_memchr.c: OK!
libft/ft_atoi.c: OK!
libft/ft_lstnew.c: OK!
libft/ft_isascii.c: OK!
libft/ft_substr.c: OK!
libft/ft_strdup.c: OK!
libft/ft_isdigit.c: OK!
libft/ft_strnstr.c: OK!
libft/ft_toupper.c: OK!
libft/ft_strlen.c: OK!
libft/ft_strmapi.c: OK!
libft/ft_lstdelone.c: OK!
libft/ft_memset.c: OK!
libft/ft_strchr.c: OK!
libft/ft_bzero.c: OK!
libft/ft_striteri.c: OK!
libft/ft_lstadd_back.c: OK!
libft/ft_isalnum.c: OK!
libft/ft_strcmp.c: OK!
libft/ft_putstr_fd.c: OK!
libft/ft_memmove.c: OK!
libft/libft.h: OK!
libft/ft_memcmp.c: OK!
minishell_tester/test_files/loop.c: OK!
includes/debug.h: OK!
includes/defs.h: OK!
includes/minishell.h: OK!
includes/token.h: OK!
includes/heredoc_signals.h: OK!
includes/limits.h: OK!
includes/parser.h: OK!
includes/redirections.h: OK!
includes/builtins.h: OK!
includes/pipeline.h: OK!
includes/env.h: OK!
includes/status.h: OK!