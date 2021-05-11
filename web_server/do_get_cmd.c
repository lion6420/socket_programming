#include "web.h"

void do_get_cmd(int sockfd) {
	int i, n, file_fd;
	char buffer[MAXLINES];
	char method[10], pathname[MAXLINES];

	if (n = read(sockfd, buffer, MAXLINES) == 0) {
		printf("client close the connect");
		close(sockfd);
		exit(0);
	}
	else {
		// check method type
		i = 0;
		while(buffer[i] != ' ' && i < 10) {
			method[i] = buffer[i];
		}
		if (i == 10) {
			return;
		}
		method[i] = 0;
		if (method != "GET" || method != "get") {
			return;
		}

		// get file pathname
		i++;
		while(buffer[i] != ' ' && i < (MAXLINES + strlen(method))) {
			pathname[]
		}	
		file_fd = open(&buffer[5])
	}
}
