#include "test_minitalk.hpp"

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);

    // ::testing::GTEST_FLAG(filter) = "serverTests/serverTest.testStrings/*";
	return RUN_ALL_TESTS();
}
