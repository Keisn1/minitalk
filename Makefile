##
# minitalk
#
# @file
# @version 0.1

SRC_DIR := src
OBJ_DIR := obj
TESTS_DIR := tests

CC := cc
CFLAGS := -Wall -Werror -Wextra

CXX := g++
CXXFLAGS := -Wall -Werror -Wextra
GTEST := -lgtest -lgtest_main -pthread

INCLUDES := -Ilibft -Iincludes
LIBFT := -Llibft -lft
FSANITIZE := -fsanitize=address

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
SERVER_SRC_FILES := $(wildcard $(SRC_DIR)/server*.c)
CLIENT_SRC_FILES := $(wildcard $(SRC_DIR)/client*.c)

TEST_OBJ_FILES := $(filter-out %_main.o, $(OBJ_FILES))
TEST_SRC_FILES := $(wildcard $(TESTS_DIR)/*.cpp)

SERVER := server
CLIENT := client

TEST_TARGET := ./run_tests

all: $(SERVER) $(CLIENT)

$(SERVER): $(SERVER_SRC_FILES)
	$(CC) $(CFLAGS) $^ -o $(SERVER) $(LIBFT) $(INCLUDES)

$(CLIENT): $(CLIENT_SRC_FILES)
	$(CC) $(CFLAGS) $^ -o $(CLIENT) $(LIBFT) $(INCLUDES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

##############################
# PHONY

clean: libft-clean
	rm -f $(TEST_TARGET) $(OBJ_FILES)

fclean: clean
	rm -rf build
	rm -f $(SERVER)
	rm -f $(CLIENT)

re: fclean all

test:
	cmake -S . -B build -DBUILD_TEST=ON && \
	cmake --build build && \
	./build/run_tests --gtest_repeat=10

build:
	cmake -S . -B build -DBUILD_TEST=OFF -DBUILD_MINITALK=ON && \
	cmake --build build

compile_commands:
	cmake -S . -B build -DBUILD_MINITALK=ON -DCMAKE_EXPORT_COMPILE_COMMANDS=ON && \
	rm compile_commands.json && \
	cp build/compile_commands.json ./compile_commands.json

libft:
	$(MAKE) -C libft

libft-re:
	$(MAKE) -C libft re

libft-clean:
	$(MAKE) -C libft clean

libft-fclean:
	$(MAKE) -C libft fclean

bear: $(TEST_TARGET)

src-files:
	@echo $(SRC_FILES)

obj-files:
	@echo $(OBJ_FILES)

test-src-files:
	@echo $(TEST_SRC_FILES)

test-obj-files:
	@echo $(TEST_OBJ_FILES)

.PHONY: test libft libft-re libft-clean libft-fclean bear src-files obj-files all build


# end
