##
# minitalk
#
# @file
# @version 0.1

SRC_DIR := src
OBJ_DIR := obj
BUILD_DIR := build
TESTS_DIR := tests

CC := cc
CFLAGS := -Wall -Werror -Wextra

INCLUDES := -Ilibft -Iincludes
LIBFT := -Llibft -lft
FSANITIZE :=

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
SERVER_SRC_FILES := $(wildcard $(SRC_DIR)/*_server.c) run/server/main.c
CLIENT_SRC_FILES := $(wildcard $(SRC_DIR)/*_client.c) run/client/main.c

TEST_OBJ_FILES := $(filter-out %_main.o, $(OBJ_FILES))
TEST_SRC_FILES := $(wildcard $(TESTS_DIR)/*.cpp)

NAME := minitalk
SERVER := server
CLIENT := client

TEST_TARGET := ./run_tests

all: libft $(SERVER) $(CLIENT)

$(NAME): libft $(SERVER) $(CLIENT)

$(SERVER): $(SERVER_SRC_FILES)
	$(CC) $(CFLAGS) $(FSANITIZE) $^ -o $(SERVER) $(LIBFT) $(INCLUDES)

$(CLIENT): $(CLIENT_SRC_FILES)
	$(CC) $(CFLAGS) $(FSANITIZE) $^ -o $(CLIENT) $(LIBFT) $(INCLUDES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

##############################
# PHONY

clean: libft-clean
	rm -f $(TEST_TARGET) $(OBJ_FILES)

fclean: clean
	rm -f $(SERVER)
	rm -f $(CLIENT)
	rm -rf $(OBJ_DIR)
	rm -rf $(BUILD_DIR)
	rm -rf .pytest_cache

re: fclean all

test: unittest integration-test integration-test-valgrind

unittest:
	cmake -S . -B build -DBUILD_TEST=ON && \
	cmake --build build && \
	./build/run_tests --gtest_repeat=10

client-test:
	make  && \
	pytest  tests/test_client.py::test_client

client-test-valgrind:
	make && \
	pytest tests/test_client.py

server-test:
	make FSANITIZE=-fsanitize=address && \
	pytest tests/test_server.py::test_server_multiple_messages && \
	pytest tests/test_server.py::test_server_long_msg

server-test-valgrind:
	make && \
	pytest tests/test_server.py::test_server_valgrind

build:
	cmake -S . -B build -DBUILD_TEST=OFF -DBUILD_MINITALK=ON && \
	cmake --build build && \
	mv build/server server && mv build/client client

compile_commands:
	cmake -S . -B build -DBUILD_MINITALK=ON -DBUILD_TEST=ON -DCMAKE_EXPORT_COMPILE_COMMANDS=ON && \
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

server-src-files:
	@echo $(SERVER_SRC_FILES)

client-src-files:
	@echo $(CLIENT_SRC_FILES)

obj-files:
	@echo $(OBJ_FILES)

test-src-files:
	@echo $(TEST_SRC_FILES)

test-obj-files:
	@echo $(TEST_OBJ_FILES)

.PHONY: test libft libft-re libft-clean libft-fclean bear server-src-files client-src-files obj-files all build


# end
