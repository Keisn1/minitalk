#include "gtest/gtest.h"
#include <cstring>
#include <signal.h>
#include <gtest/gtest.h>
#include <unistd.h>
#include "minitalk.h"


typedef void (*FunctionPtr)(void);

struct serverTestParameter {
	const char* msg;
	const char* want;
};

class serverTest : public ::testing::TestWithParam<serverTestParameter> {
protected:
	void SetUp() override {
		signal_handler(-1);
	}
};

void send_char(char c) {
	int count = 0;
	while (count < 8) {
		unsigned char bit = c >> count & 1;
		if (bit)
			kill(getppid(), SIGUSR1);
		else
			kill(getppid(), SIGUSR2);
		usleep(42);
		count++;
	}
}

TEST_P(serverTest, testStrings) {
	serverTestParameter params = GetParam();

	signal(SIGUSR1, signal_handler); // signal_handler is the src-code function
	signal(SIGUSR2, signal_handler); // signal_handler is the src-code function

	testing::internal::CaptureStdout();

	pid_t pid = fork();
	ASSERT_NE(pid, -1) << "Forking failed";

	if (pid == 0) {  // Child process
		char* msg = (char*)params.msg;
		while (*msg) {
			send_char(*msg);
			msg++;
		}
		send_char(*msg);
		_exit(0);  // Exit child process
	} else {  // Parent process
		int status;
		waitpid(pid, &status, 0);  // Wait for child process to finish
		std::string stdout = testing::internal::GetCapturedStdout();
        EXPECT_STREQ(params.want, stdout.c_str()) << "Signal handler was not called or message incorrect";
	}
}

INSTANTIATE_TEST_SUITE_P(serverTests, serverTest,
						 testing::Values(
							 serverTestParameter{"!", "!"},
							 serverTestParameter{"x", "x"},
							 serverTestParameter{"x!", "x!"},
							 serverTestParameter{"abc", "abc"},
							 serverTestParameter{"Ich bin toll", "Ich bin toll"}
							 ));

////////////////////////////////////////////////////
// test messages that are not multiple of 8 bits

class testIncompleteStrings : public ::testing::TestWithParam<serverTestParameter> {
protected:
	void SetUp() override {
		signal_handler(-1);
	}
};

void sigusr1_n_time(int n) {
	int count = 0;
	while (count++ < n) {
		kill(getppid(), SIGUSR1);
		usleep(42);
	}
}

TEST_P(testIncompleteStrings, testIncompleteStrings) {
	serverTestParameter params = GetParam();

	signal(SIGUSR1, signal_handler); // signal_handler is the src-code function
	signal(SIGUSR2, signal_handler); // signal_handler is the src-code function

	testing::internal::CaptureStdout();

	pid_t pid = fork();
	ASSERT_NE(pid, -1) << "Forking failed";

	if (pid == 0) {  // Child process
		char* msg = (char*)params.msg;
		while (*msg) {
			unsigned char c = *msg;
				sigusr1_n_time(c - '0');
			msg++;
		}
		_exit(0);  // Exit child process
	} else {  // Parent process
		int status;
		waitpid(pid, &status, 0);  // Wait for child process to finish
		std::string stdout = testing::internal::GetCapturedStdout();
        EXPECT_STREQ(params.want, stdout.c_str()) << "Signal handler was not called or message incorrect";
	}
}

INSTANTIATE_TEST_SUITE_P(serverTests, testIncompleteStrings,
						 testing::Values(
							 serverTestParameter{"0", ""},
							 serverTestParameter{"1", ""},
							 serverTestParameter{"2", ""},
							 serverTestParameter{"3", ""},
							 serverTestParameter{"4", ""},
							 serverTestParameter{"4", ""},
							 serverTestParameter{"5", ""},
							 serverTestParameter{"6", ""},
							 serverTestParameter{"7", ""}
							 // serverTestParameter{"!", "!"},
							 // serverTestParameter{"x", "x"}
							 // serverTestParameter{"x!", "x!"}
							 ));
