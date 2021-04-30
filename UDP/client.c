#include "unp.h"

int main(int argc, char** argv) {
	int sockfd;
	struct sockaddr_in servaddr;

	if (argc != 2) {
		printf("usage: client <IP address>");
	}
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	dg_cli(stdin, sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr));
	
	exit(0);
}
