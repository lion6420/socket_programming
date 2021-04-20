#include "unp.h"

Sigfunc* signal(int signo, Sigfunc* func) {
	struct sigaction act, oact;

	act.sa_handler = func;
	sigemptyset(act.sa_mask);
	act.sa_flag = 0;


}
