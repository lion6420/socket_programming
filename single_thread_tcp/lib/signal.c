#include "unp.h"

Sigfunc* signal(int signo, Sigfunc* func) {
	struct sigaction act, oact;

	act.sa_handler = func;
	sigemtyset(&act.sa_mask);
	act.sa_flag = 0;

	if (sigaction(signo, &act, &oact)<0) {
		return (SIG_ERR);
	}
	
	return (oact.sa_handler);
}
