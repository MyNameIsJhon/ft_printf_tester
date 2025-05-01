###############################################################################
# VARIABLES
###############################################################################

# Binary name
default: NAME = ftprintf_tester
NAME         = ftprintf_tester

# Directories
SRC_DIR      = srcs
INC_DIR      = includes
LIBFT_DIR    = ../libft

# Libraries
LIBFT_PRINTF_LIB = ../libftprintf.a
LIBFT_LIB        = $(LIBFT_DIR)/libft.a
LIBS             = $(LIBFT_PRINTF_LIB) $(LIBFT_LIB)

# Include flags
INCLUDES    = -I$(INC_DIR) -I$(LIBFT_DIR) -I.

# Sources and objects
SRCS        = $(wildcard $(SRC_DIR)/*.c)
OBJS        = $(SRCS:$(SRC_DIR)/%.c=$(SRC_DIR)/%.o)

# Compiler and flags
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror $(INCLUDES)
LDFLAGS     =

# Optional modes
# make DEBUG=1    -> build with AddressSanitizer
# make COV=1      -> build with coverage
ifeq ($(DEBUG),1)
	CFLAGS += -g -fsanitize=address
endif

ifeq ($(COV),1)
	CFLAGS += -g -O0 --coverage
	LDFLAGS += --coverage
endif

# Valgrind flags
VALGRIND_FLAGS = --leak-check=full --track-origins=yes --show-leak-kinds=all

###############################################################################
# RULES
###############################################################################

.PHONY: all run test leak clean fclean re

# Default: build tester
all: $(NAME)

# Link executable with static libs
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

# Compile sources
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run tester
run: all
	./$(NAME)

test: run

# Run under Valgrind
leak: all
	valgrind $(VALGRIND_FLAGS) ./$(NAME)

# Clean objects
clean:
	rm -f $(OBJS)

# Clean objects and binary
fclean: clean
	rm -f $(NAME)

# Rebuild everything
re: fclean all

###############################################################################
# USAGE EXAMPLES
###############################################################################
# make                           # build normally
# make DEBUG=1                   # with AddressSanitizer
# make COV=1                     # with coverage
# make run                       # build and run
# make leak                      # build and run under Valgrind
# make clean fclean re           # clean and rebuild
