#include "unp.h"

void start_connect(struct file* fptr) {
	int n;
	struct addrinfo hints, *res;

	bzero(&hint, sizeof(struct addrinfo));
	hints.ai_flag = AI_CONONNAME;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	
	if ((n = getaddrinfo(fptr->host, SERV, &hints, &res)) != 0) {
		printf("getaddrinfo error");
	}

	fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	fptr->f_fd = fd;

	flags = fcntl(fd, GETFL, 0);
	fcntl(fd, SETFL, flags | O_NONBLOCK); // non-block socket
	
	if ((n = connect(fd, res->ai_addr, res->ai_addrlen)) < 0) {
		if (errno != EINPROGRESS)
			printf("nonblocking connect error");
		fptr->f_flags = F_CONNECTING;
		FD_SET(fd, &rset);
		FD_SET(fd, &wset);
		if (fd > maxfd)
			maxfd = fd;
	}
	else if (n >= 0) { // connection established
		write_get_cmd(fptr);
	}
	
}
