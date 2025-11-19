# **************************************************************************** #
#                                   Minishell                                  #
# **************************************************************************** #

# Colors
RST 	 = "\033[0m"
GREEN    = "\033[32m"
YELLOW   = "\033[33m"
RED 	 = "\033[31m"
BLUE	 = "\033[34m"

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
SRC_MAIN := main.c prompt.c signals.c utils.c path.c storage.c cleaner.c \
			single_command.c

# Files builtins
SRC_BUILTINS := echo.c cd.c pwd.c env.c export.c export_utils.c \
                unset.c exit.c run_builtin.c export_with_args.c

# Files parser
SRC_PARSER := parse_tokens.c parse_utils.c parser_line.c \
				tokenizer.c token_free.c token_helper.c \
				token_quote.c token_list.c expand_tokens_utils.c \
				expand_tokens.c expand_utils.c parse_tokens_utils.c \
				token_helper_operator.c parse_tokens_process.c \
				parser_args.c parser_words.c parser_redirs.c \
				parse_tokens_process_utils.c

# Files env
SRC_ENV := env.c env_utils.c env_local.c env_local_utils.c env_create_utils.c

# Files pipeline
SRC_EXECUTION := execute_pipeline.c executor.c executor_utils.c child_process.c \
				child_process_utils.c

SRC_REDIRECTION := apply_redirections.c open_files.c utils_redir.c heredoc_utils.c \
				heredoc_signals.c

SRC_STATUS := status.c

# Формируем полные пути
SRC :=  $(addprefix $(SRC_DIR)/, $(SRC_MAIN)) \
		$(addprefix $(SRC_DIR)/builtins/, $(SRC_BUILTINS)) \
		$(addprefix $(SRC_DIR)/env/, $(SRC_ENV)) \
		$(addprefix $(SRC_DIR)/parser/, $(SRC_PARSER)) \
		$(addprefix $(SRC_DIR)/executors/, $(SRC_EXECUTION)) \
		$(addprefix $(SRC_DIR)/redirections/, $(SRC_REDIRECTION)) \
		$(addprefix $(SRC_DIR)/status/, $(SRC_STATUS))

# Object files
OBJS := $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

# Default target
all: $(NAME)

# Create binary
$(NAME): $(OBJS) $(LIBFT)
	@echo $(GREEN)"Compiling $(NAME)..."$(RST)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(LIBS)
	@echo $(GREEN)"Finished Compiling!" $(RST)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# Compile .c to .o
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Cleaning
clean:
	@echo $(BLUE)"Cleaned!"$(RST)
	@$(RM) -r $(OBJ_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) clean

fclean: clean
	@echo $(RED)"Fully cleaned!"$(RST)
	@$(RM) $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
