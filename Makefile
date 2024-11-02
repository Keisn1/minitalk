##
# minitalk
#
# @file
# @version 0.1

TESTS_DIR := tests

INCLUDES := -Ilibft -Iincludes
LIBFT := -Llibft -lft
FSANITIZE := -fsanitize=address

CXX := g++
CXXFLAGS := -Wall -Werror -Wextra
GTEST := -lgtest -lgtest_main -pthread

SRC_FILES := $(wildcard *.c)

TEST_SRC_FILES := $(wildcard $(TESTS_DIR)/*.cpp)

TEST_TARGET := ./run_tests
UNIT_TEST := -DUNIT_TEST

$(TEST_TARGET): $(TEST_SRC_FILES) $(SRC_FILES)
	$(CXX) $(CXXFLAGS)  $(SRC_FILES) $(TEST_SRC_FILES) -o $(TEST_TARGET) $(INCLUDES) $(FSANITIZE) $(GTEST) $(UNIT_TEST) $(LIBFT)

clean: libft-clean
	rm -f $(TEST_TARGET)

test: $(TEST_TARGET)
	- $(TEST_TARGET)

libft:
	$(MAKE) -C libft

libft-re:
	$(MAKE) -C libft re

libft-clean:
	$(MAKE) -C libft clean

libft-fclean:
	$(MAKE) -C libft fclean

bear: $(TEST_TARGET)

.PHONY: test libft libft-re libft-clean libft-fclean bear


# end
