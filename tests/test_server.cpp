#include <signal.h>
#include <gtest/gtest.h>
#include <unistd.h>
#include "minitalk.h"


struct serverTestParameter {
	const char* msg;
	const char* want;
};

class serverTest : public ::testing::TestWithParam<serverTestParameter> {
protected:
  void SetUp() override {
		struct sigaction action;
		action.sa_sigaction = &string_handler;
		action.sa_flags = 0;
		sigemptyset(&action.sa_mask);
		sigaction(SIGUSR1, &action, NULL);
		sigaction(SIGUSR2, &action, NULL);
  }
};

void send_char(char c) {
	int count = 0;
	while (count < 8) {
		unsigned char bit = (c >> count) & 1;
		if (bit)
			raise(SIGUSR1);
		else
			raise(SIGUSR2);
		count++;
	}
}

TEST_P(serverTest, testStrings) {
	serverTestParameter params = GetParam();
	testing::internal::CaptureStdout();

	char* msg = (char*)params.msg;
	while (*msg) {
		send_char(*msg);
		msg++;
	}
	send_char(*msg);

	std::string stdout = testing::internal::GetCapturedStdout();
	EXPECT_STREQ(params.want, stdout.c_str()) << "Signal handler was not called or message incorrect";
}

INSTANTIATE_TEST_SUITE_P(serverTests, serverTest,
						 testing::Values(
							 serverTestParameter{"!", "!\n"},
							 serverTestParameter{"x", "x\n"},
							 serverTestParameter{"x!", "x!\n"},
							 serverTestParameter{"abc", "abc\n"},
							 serverTestParameter{"Ich bin toll", "Ich bin toll\n"},
							 serverTestParameter{"a;ldskjf asdkljfl;asjdf l;asjdfl;kjasl dfkkjasldfjl;aksjdfl;kkjas lkf asd flkaj sdlf;kkjalsdfj", "a;ldskjf asdkljfl;asjdf l;asjdfl;kjasl dfkkjasldfjl;aksjdfl;kkjas lkf asd flkaj sdlf;kkjalsdfj\n"}
							 ));

////////////////////////////////////////////////////
// test messages that are not multiple of 8 bits

// class testIncompleteStrings : public ::testing::TestWithParam<serverTestParameter> {};

// void sigusr1_n_time(int n) {
// 	int count = 0;
// 	while (count++ < n) {
// 		kill(getppid(), SIGUSR1);
// 		usleep(42);
// 	}
// }

// TEST_P(testIncompleteStrings, testIncompleteStrings) {
// 	serverTestParameter params = GetParam();

// 	signal(SIGUSR1, string_handler); // signal_handler is the src-code function
// 	signal(SIGUSR2, string_handler); // signal_handler is the src-code function

// 	testing::internal::CaptureStdout();

// 	pid_t pid = fork();
// 	ASSERT_NE(pid, -1) << "Forking failed";

// 	if (pid == 0) {  // Child process
// 		char* msg = (char*)params.msg;
// 		while (*msg) {
// 			unsigned char c = *msg;
// 			sigusr1_n_time(c - '0');
// 			msg++;
// 		}
// 		_exit(0);  // Exit child process
// 	} else {  // Parent process
// 		int status;
// 		waitpid(pid, &status, 0);  // Wait for child process to finish
// 		std::string stdout = testing::internal::GetCapturedStdout();
//         EXPECT_STREQ(params.want, stdout.c_str()) << "Signal handler was not called or message incorrect";
// 	}
// }

// INSTANTIATE_TEST_SUITE_P(serverTests, testIncompleteStrings,
// 						 testing::Values(
// 							 serverTestParameter{"0", ""},
// 							 serverTestParameter{"1", ""},
// 							 serverTestParameter{"2", ""},
// 							 serverTestParameter{"3", ""},
// 							 serverTestParameter{"4", ""},
// 							 serverTestParameter{"4", ""},
// 							 serverTestParameter{"5", ""},
// 							 serverTestParameter{"6", ""},
// 							 serverTestParameter{"7", ""}
// 							 ));
