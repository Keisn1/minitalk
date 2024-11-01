#include <cstring>
#include <signal.h>
#include <gtest/gtest.h>
#include "minitalk.h"


TEST(serverTests, serverTest) {
	signal(SIGUSR1, signal_handler);

	pid_t pid = fork();
	ASSERT_NE(pid, -1) << "Forking failed";

	if (pid == 0) {  // Child process
// Send a signal to ourselves
		kill(getppid(), SIGUSR1);
		_exit(0);  // Exit child process
	} else {  // Parent process
		int status;
		waitpid(pid, &status, 0);  // Wait for child process to finish
		// Check the flag to see if the signal handler was called
        EXPECT_STREQ("Signal received", (char*)got_signal_msg) << "Signal handler was not called or message incorrect";
	}
}

