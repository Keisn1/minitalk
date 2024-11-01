#include "minitalk.h"
#include <stdlib.h>
#include <string.h>

volatile char* got_signal_msg = NULL;

void signal_handler(int signal) {
	if (signal) {

	}
	if (got_signal_msg == NULL) {
		got_signal_msg = (volatile char*)malloc(32);
	}
	strcpy((char*)got_signal_msg, "Signal received");
}
