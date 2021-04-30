#include "unp.h"

void dg_echo(int sockfd, struct sockaddr* cliaddr, socklen_t clilen) {
	int n;
	char buff[MAXLINE];

	for(;;) {
		n = recvfrom(sockfd, buff, MAXLINE, 0, cliaddr, &clilen);
		sendto(sockfd, buff, n, 0, cliaddr, clilen);
	}

}
