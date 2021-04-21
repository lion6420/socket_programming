#include "unp.h"
void str_cli(FILE* fp, int sockfd) {
	char sendline[MAXLINE], recvline[MAXLINE];
	ssize_t n;

	while(fgets(sendline, MAXLINE, fp) != NULL) {
		write(sockfd, sendline, strlen(sendline));

		if ((n = read(sockfd, recvline, MAXLINE)) == 0) {
			printf("str_cli: server terminated prematurely");
		}
		recvline[n] = 0;
		fputs(recvline, stdout);
	}
}
