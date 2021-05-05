#include "unp.h"

static void recvfrom_alarm(int);

void dg_cli(FILE* fp, int sockfd, struct sockaddr* servaddr, socklen_t servlen) {
	const int on = 1;
	char sendline[MAXLINE], recvline[MAXLINE];

	struct sockaddr_in replyaddr;
	char replyaddr_str;
	socklen_t replylen;
	setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));

	signal(SIGALRM, recvfrom_alarm);
	while(fgets(sendline, MAXLINE, fp) != NULL) {
		alarm(5);
		sendto(sockfd, sendline, strlen(sendline), 0, servaddr, servlen);
		for(;;) {
			n = recvfrom(sockfd, recvline, MAXLINE, 0, (struct sockaddr *) &replyaddr, &replylen);
			if (n < 0) {
				if (errno == EINTR) {
					break;
				}
				else {
					printf("recvfrom error");
				}
			}
			else {
				inet_ntop(AF_INET, (struct sockaddr*) replyaddr, replyaddr_str, replylen);
				printf("recieve from %s: %s", replyaddr_str, recvline);
			}
		}
	}
}

static void recvfrom_alarm(int signo) {
	return;
}
