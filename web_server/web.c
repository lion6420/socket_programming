#include "web.h"

int main() {
	int listenfd, connfd;
	struct sockaddr_in servaddr, cliaddr;
	socklen_t clilen;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(listenfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0) {
		printf("socket bind error.");
		exit(0);
	}
	listen(listenfd, 64);
	
	for(;;) {
		clilen = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr*) &cliaddr, &clilen);

		if (fork() == 0) { // child
			close(listenfd);
			do_get_cmd(connfd);
		}
		else {
			close(connfd);
		}
	}

	exit(0);
}
