#include "test_minitalk.hpp"

class clientSignalHandlerTestFixture : public ::testing::Test {
	protected:
		void SetUp() override {
			signal(SIGUSR1, &client_signal_handler);
			signal(SIGUSR2, &client_signal_handler);
		}

		void TearDown() override {
			signal(SIGUSR1, SIG_DFL);
			signal(SIGUSR2, SIG_DFL);
		}
};

TEST_F(clientSignalHandlerTestFixture, clientSignalHandlerTest) {
	ASSERT_EQ(g_server_signal_received, 0);
	raise(SIGUSR1);
	ASSERT_EQ(g_server_signal_received, 1);

	testing::internal::CaptureStdout();
	raise(SIGUSR2);
	std::string stdout = testing::internal::GetCapturedStdout();
	EXPECT_STREQ("Server: \"Message received\"\n", stdout.c_str()) << "Signal handler was not called or message incorrect";
}
