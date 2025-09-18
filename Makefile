# **************************************************************************** #
#                                   Minishell                                  #
# **************************************************************************** #

# Colors
RST = \033[0m
G   = \033[32m
Y   = \033[33m

# Project
NAME    := minishell
SRC_DIR := src
INC_DIR := includes

LIBFT_DIR := libft
LIBFT     := $(LIBFT_DIR)/libft.a

# Compiler
CC      := cc
CFLAGS  := -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR)
LIBS    := -lreadline -lncurses
RM      := rm -f

# Files src
SRC_MAIN := main.c executor.c prompt.c signals.c utils.c path.c \
            executor_utils.c

# Files builtins
SRC_BUILTINS := builtin_echo.c builtin_cd.c builtin_pwd.c \
                builtin_env.c builtin_export.c builtin_export_utils.c \
                builtin_unset.c builtin_exit.c run_builtin.c

# Files parser
SRC_PARSER := parser_tokens.c tokenizer.c parser_line.c

# Files env
SRC_ENV := env.c env_utils.c

# Files pipeline
SRC_PIPELINE := execute_pipeline.c

SRC_REDIRECTION := apply_redirections.c open_files.c utils_redir.c

# Формируем полные пути
SRC :=  $(addprefix $(SRC_DIR)/, $(SRC_MAIN)) \
		$(addprefix $(SRC_DIR)/builtins/, $(SRC_BUILTINS)) \
		$(addprefix $(SRC_DIR)/env/, $(SRC_ENV)) \
		$(addprefix $(SRC_DIR)/parser/, $(SRC_PARSER)) \
		$(addprefix $(SRC_DIR)/pipeline/, $(SRC_PIPELINE)) \
		$(addprefix $(SRC_DIR)/redirections/, $(SRC_REDIRECTION))

# Quiet build
QUIET = $(if $(filter 0,$(VERBOSE)),@,)

OBJS := $(SRC:.c=.o)

# Default target
all: $(NAME)

# Create binary
$(NAME): $(OBJS) $(LIBFT)
	@printf $(G)"[INFO] Compiling $(NAME)..."$(RST)
	$(QUIET)$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(LIBS)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# Compile .c to .o
%.o: %.c
	@printf $(Y)"[CC] $<"$(RST)
	$(QUIET)$(CC) $(CFLAGS) -c $< -o $@

# Cleaning
clean:
	@printf $(Y)"[CLEAN]"$(RST)
	$(QUIET)$(RM) $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@printf $(Y)"[FCLEAN]"$(RST)
	$(QUIET)$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re