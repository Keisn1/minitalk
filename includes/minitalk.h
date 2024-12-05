#ifndef MINITALK_H
# define MINITALK_H

#include <signal.h>

# ifdef __cplusplus
extern "C"
{
# endif

	void string_handler(int sig, siginfo_t * siginfo, void* ucontext);
	void interrupt_handler(int signal);
	void send_char(char c, pid_t pid);

# ifdef __cplusplus
}
# endif

#endif // MINITALK_H
