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

# Compiler
CC      := cc
CFLAGS  := -Wall -Wextra -Werror -I$(INC_DIR)
LIBS    := -lreadline -lncurses
RM      := rm -f

# Source files
SRC_FILES := main.c executor.c parser.c prompt.c signals.c utils.c path.c builtin_echo.c
SRC       := $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS      := $(SRC:.c=.o)

# Quiet build
QUIET = $(if $(filter 0,$(VERBOSE)),@,)

# Default target
all: $(NAME)

# Create binary
$(NAME): $(OBJS)
	@printf $(G)"[INFO] Compiling $(NAME)..."$(RST)
	$(QUIET)$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

# Compile .c to .o
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@printf $(Y)"[CC] $<"$(RST)
	$(QUIET)$(CC) $(CFLAGS) -c $< -o $@

# Cleaning
clean:
	@printf $(Y)"[CLEAN]"$(RST)
	$(QUIET)$(RM) $(OBJS)

fclean: clean
	@printf $(Y)"[FCLEAN]"$(RST)
	$(QUIET)$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re