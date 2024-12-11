##
#libft
#
#@file
#@version 0.1

#Compiler and flags
CC := cc
CXX := g++
CFLAGS := -Wall -Wextra -Werror

#Directories and extensions
BIN_DIR := ./bin
TESTS_DIR := ./tests

#Source files
SRC_FILES := $(wildcard *.c)
OBJ_FILES := $(SRC_FILES:%.c=%.o)

#Library name
NAME := libft.a

# Executable names
.DEFAULT_GOAL := all

############ Rules ##################
#Mandatory targets
all: $(NAME)

$(NAME): $(OBJ_FILES)
	ar rc $@ $^

bonus: $(OBJ_FILES_BONUS)
	ar r $(NAME) $^

# Compile C source files to object files
$%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

############ PHONY ##################
clean:
	rm -f $(OBJ_FILES) $(TEST_OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

norminette:
	norminette -R CheckForbiddenSourceHeader -R CheckDefine

############ PRINTING ##################
#Phony targets
.PHONY: all bonus clean fclean re bear test-fsanitize norminette

#Printing
print_srcs:
	@echo $(SRC_FILES)

print_objs:
	@echo $(OBJ_FILES)

print_test_files:
	@echo $(TEST_FILES)

print_test_objs:
	@echo $(TEST_OBJ_FILES)

print_test_target:
	@echo $(TEST_TARGET)
#end
