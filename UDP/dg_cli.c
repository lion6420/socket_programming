#include "unp.h"

void dg_cli(FILE* fp, int sockfd, struct sockaddr* servaddr, socklen_t servlen) {
	int n;
	socklen_t len;
	char sendline[MAXLINE], recvline[MAXLINE + 1];

	while(fgets(sendline, MAXLINE, fp) != NULL) {
		sendto(sockfd, sendline, strlen(sendline), 0, servaddr, servlen);

		n = recvfrom(sockfd, recvline, MAXLINE, 0, servaddr, &servlen);
		recvline[n] = 0;
		fputs(recvline, stdout);
	}
}
