#ifndef MINITALK_H
# define MINITALK_H

#include <signal.h>
#include <unistd.h>
#include <stdbool.h>
#include "libft.h"
#include <errno.h>

extern volatile sig_atomic_t	g_server_signal_received;

int	validate_pid_str(char *pid);
int	argument_validation(int argc, char *argv[]);
int	server_pid_validation(int server_pid);
void	client_signal_handler(int signal);
void string_handler(int sig, siginfo_t * siginfo, void* ucontext);
void interrupt_handler(int signal);
void send_char(char c, pid_t pid);
void	send_msg(char *msg, pid_t server_pid);

#endif // MINITALK_H
