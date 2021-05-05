#include "unp.h"

int main(int argc, char** argv) {
	int sockfd;
	struct sockaddr_in cliaddr;
	if (argc != 2) {
		printf("usage: client <IP address>")
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&cliaddr, sizeof(cliaddr));
	cliaddr.sin_family = AF_INET;
	cliaddr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, argv[1], &cliaddr.sin_addr);

	connect(sockfd, (struct sockaddr*) &cliaddr, sizeof(cliaddr));

	str_cli(stdin, sockfd);

	exit(0);
}
