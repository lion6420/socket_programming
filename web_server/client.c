#include "web.h"

int main(int argc, char** argv) {
	struct sockaddr_in servaddr;
	int n, sockfd;
	char buffer[MAXLINES];
	char cmd[] = "GET %s HTTP/1.1";

	if (argc != 3) {
		printf("usage: web <IP address> <filename1>\n");
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr));
	
	n = snprintf(buffer, MAXLINES, cmd, argv[2]);

	write(sockfd, buffer, n);

	while((n = read(sockfd, buffer, MAXLINES)) > 0) {
		fputs(buffer, stdout);
	}
	close(sockfd);
	exit(0);
}
