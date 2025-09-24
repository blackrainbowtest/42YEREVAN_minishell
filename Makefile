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
DEBUGING := 0

LIBFT_DIR := libft
LIBFT     := $(LIBFT_DIR)/libft.a

# Compiler
CC      := cc
# -g3 -fsanitize=address,undefined,leak
CFLAGS  := -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR) -DDEBUGING=$(DEBUGING)
LIBS    := -lreadline -lncurses
RM      := rm -f

# Object files directory
OBJ_DIR := obj

# Files src
SRC_MAIN := main.c prompt.c signals.c utils.c path.c \

# Files builtins
SRC_BUILTINS := echo.c cd.c pwd.c env.c export.c export_utils.c \
                unset.c exit.c run_builtin.c

# Files parser
SRC_PARSER := parser_tokens.c parser_line.c \
				tokenizer.c token_free.c token_helper.c \
				token_quote.c token_list.c \
				expand_tokens.c expand_utils.c

# Files env
SRC_ENV := env.c env_utils.c env_local.c env_local_utils.c

# Files pipeline
SRC_EXECUTION := execute_pipeline.c executor.c executor_utils.c

SRC_REDIRECTION := apply_redirections.c open_files.c utils_redir.c

SRC_DEBUG := debug_parser.c debug_tokens.c

SRC_STATUS := status.c

# Формируем полные пути
SRC :=  $(addprefix $(SRC_DIR)/, $(SRC_MAIN)) \
		$(addprefix $(SRC_DIR)/builtins/, $(SRC_BUILTINS)) \
		$(addprefix $(SRC_DIR)/env/, $(SRC_ENV)) \
		$(addprefix $(SRC_DIR)/parser/, $(SRC_PARSER)) \
		$(addprefix $(SRC_DIR)/executors/, $(SRC_EXECUTION)) \
		$(addprefix $(SRC_DIR)/redirections/, $(SRC_REDIRECTION)) \
		$(addprefix $(SRC_DIR)/debug/, $(SRC_DEBUG)) \
		$(addprefix $(SRC_DIR)/status/, $(SRC_STATUS))

# Quiet build
QUIET = $(if $(filter 0,$(VERBOSE)),@,)

# Object files
OBJS := $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

# Default target
all: $(NAME)

# Valgrind check
val: CFLAGS += -g3
val: all
	@printf "$(G)[VALGRIND] Running Valgrind on $(NAME)..."$(RST)"\n"
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME)

# Create binary
$(NAME): $(OBJS) $(LIBFT)
	@printf $(G)"[INFO] Compiling $(NAME)..."$(RST)"\n"
	$(QUIET)$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(LIBS)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# Compile .c to .o
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf $(Y)"[CC] $<"$(RST)"\n"
	$(QUIET)$(CC) $(CFLAGS) -c $< -o $@

# Cleaning
clean:
	@printf $(Y)"[CLEAN]"$(RST)"\n"
	$(QUIET)$(RM) -r $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@printf $(Y)"[FCLEAN]"$(RST)"\n"
	$(QUIET)$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
