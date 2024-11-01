#ifndef MINITALK_H
#define MINITALK_H

#include <signal.h>

extern volatile char* got_signal_msg;

void signal_handler(int signal);

#endif // MINITALK_H
