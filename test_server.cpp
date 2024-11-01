#include "gtest/gtest.h"
#include <cstring>
#include <signal.h>
#include <gtest/gtest.h>
#include "minitalk.h"


typedef void (*FunctionPtr)(void);

struct serverTestParameter {
	FunctionPtr sig_calls;
	const char* want;
};

class serverTest : public ::testing::TestWithParam<serverTestParameter>{};

void sigusr1() {
	kill(getppid(), SIGUSR1);
}

TEST_P(serverTest, serverTest) {
	serverTestParameter params = GetParam();

	signal(SIGUSR1, signal_handler); // signal_handler is the src-code function

	pid_t pid = fork();
	ASSERT_NE(pid, -1) << "Forking failed";

	if (pid == 0) {  // Child process
		params.sig_calls();		// goes through the signal calls defined in sig_calls
		_exit(0);  // Exit child process
	} else {  // Parent process
		int status;
		waitpid(pid, &status, 0);  // Wait for child process to finish
		// Check the flag to see if the signal handler was called
        EXPECT_STREQ("Signal received", (char*)got_signal_msg) << "Signal handler was not called or message incorrect";
	}
}

INSTANTIATE_TEST_SUITE_P(serverTests, serverTest,
                         testing::Values(
							 serverTestParameter{sigusr1, "Signal received"}
                             ));
