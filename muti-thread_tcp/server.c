#include "unp.h"

int main() {
	int listenfd, connfd;
	socklen_t clilen;
	struct sockaddr_in servaddr, cliaddr;

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	bind(listenfd, (struct sockaddr*) servaddr, sizeof(servaddr));
	listen(listenfd, LISTENQ);

	for(;;) {
		clilen = sizeof(cliaddr);


	}
}
