#include "minitalk.h"
#include <unistd.h>

void signal_handler(int signal) {
	static unsigned signals_received = 0;

#ifdef UNIT_TEST				/* PreprocessorDirective */
	if (signal == -1) {
		signals_received = 0;
		return;
	}
#endif

	signals_received++;
	if (signals_received == 8) {
		char c = '!';
		write(1, &c, STDOUT_FILENO);
	}
}
