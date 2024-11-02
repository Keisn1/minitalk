##
# minitalk
#
# @file
# @version 0.1

CXX := g++
CXXFLAGS := -Wall -Werror -Wextra
FSANITIZE := -fsanitize=address
GTEST := -lgtest -lgtest_main -pthread

SRC_FILES := $(wildcard *.c)

TEST_FILES := $(wildcard *.cpp)
TEST_TARGET := run_tests
UNIT_TEST := -DUNIT_TEST

test:
	$(CXX) -o $(TEST_TARGET) $(SRC_FILES) $(TEST_FILES) $(CXXFLAGS) $(FSANITIZE) $(GTEST) $(UNIT_TEST)
	./$(TEST_TARGET)

.PHONY: test

# end
