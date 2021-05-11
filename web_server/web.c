#include "unp.h"

int main(int argc, char** argv) {
	int files, nlefttoread, nlefttoconn, nconn, maxnconn, flags, fd;

	if (argc < 5) {
		printf("usage: web <#conns> <hostname> <homepage> <file1> <file2> ...");
	}

	nfiles = min(argc-4, MAXLINES);

	for(int i=0; i<nfiles; i++) {
		files[i].f_name = argv[i+4];
		files[i].f_host = argv[2];
		files[i].f_flags = 0;
	}

	FD_ZERO(&rset);
	FD_ZERO(&wset);
	maxfd = -1;
	maxnconn = atoi(argv[1]);
	nlefttoread = nlefttoconn = nfiles;
	nconn = 0;
	
	while(nlefttoread > 0) {
		while (nconn < maxnconn && nlefttoconn > 0) {
			for (int i=0; i<nfiles; i++) {
				if (files[i].f_flags == 0)
					break;
			}
			start_connect(&files[i]);
			nlefttoconn--;
			nconn++;
		}

		rs = rset;
		ws = wset;
		n = select(maxfd+1, &rs, &ws, NULL, NULL);

		for (int i=0; i<nfiles; i++) {
			flags = files[i].f_flags;
			if (flags == 0 || flags & F_DONE)
				continue;
			fd = files[i].f_fd;
			if (flags & F_CONNECTING &&
			    (FD_ISSET(fd, &rset) || FD_ISSET(fd, &wset))) {
				FD_CLR(fd, &wset);
				write_get_cmd(&files[i]);
			}
			else if (flags & F_READING && FD_ISSET(fd, &rset)) {
				if ((n = read(fd, buf, sizeof(buf))) == 0) {
					printf("end-of-file on %s \n", files[i].f_name);
					close(fd);
					FD_CLR(fd, &rset);
					nconn--;
					nlefttoread--;
				}
				else {
					printf("read %d bytes from %s \n", n, files[i].f_name);
			}
		}
	}
	exit(0);
	
}
