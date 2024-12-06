#ifndef MINITALK_H
# define MINITALK_H

#include <signal.h>
#include <unistd.h>
#include <stdbool.h>

void	signal_handler(int signal);
void string_handler(int sig, siginfo_t * siginfo, void* ucontext);
void interrupt_handler(int signal);
void send_char(char c, pid_t pid);
void	send_msg(char *msg, pid_t server_pid);

#endif // MINITALK_H
