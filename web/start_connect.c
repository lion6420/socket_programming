#include "unp.h"

void start_connect(struct file* fptr) {
	struct sockaddr_in servaddr;
	socklen_t servlen;
	int flags, n

	fptr->f_fd = socket(AF_INET, SOCK_STREAM, 0);
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, fptr->f_host, &servaddr.sin_addr);

	/* set socket non-blocking */
	flags = fcntl(fptr->f_fd, F_GETFL, 0);
	fcntl(fptr->f_fd, F_SETFL, flags|O_NONBLOCK);

	if (n = connect(fptr->fd, (struct sockaddr*) &servaddr, sizeof(servaddr) < 0)) {
		if (errno != EINPROGRESS) {
			printf("nonblocking connect error");
		}
		fptr->f_flags = F_CONNECTING;
		FD_SET()
	}
}
