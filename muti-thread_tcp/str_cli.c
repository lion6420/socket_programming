#include "unp.h"

static int sockfd;
static FILE* fp;

void str_cli(FILE* fp_arg, int sockfd_arg) {
	char recvline[MAXLINE];
	int n;
	pthread_t tid;

	sockfd = sockfd_arg;
	fp = fp_arg;

	pthread_create(*tid, NULL, copyto, NULL);

	while((n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0;
		fputs(recvline, stdout)
	}
}

void* copyto(void* arg) {
	char sendline[MAXLINE];
	while(fgets(sendline, MAXLINE, fp) != NULL) {
		write(sockfd, sendline, strlen(sendline));
	}

	shutdown(sockfd, SHUT_WR);
	
	return NULL;
}
