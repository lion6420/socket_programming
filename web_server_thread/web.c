#include "unp.h"
#include <pthread.h>

#define MAXFILES 20
#define SERV "80"

struct file {
	char* f_name;
	char* f_host;
	int f_fd;
	int f_flags;
	pthread_t f_tid;
} file[MAXFILES];

#define F_CONNECTING 1
#define F_READING 2
#define F_DONE 4
#define GET_CMD "GET %s HTTP/1.0\r\n\r\n"

int nconn, nfiles, nlefttoconn, nlefttoread;
int ndone = 0;
pthread_mutex_t ndone_mutex;
pthread_cond_t ndone_cond;

void* do_get_read(void*);
void home_page(const char*, const char*);
void write_get_cmd(struct file*);

int main(int argc, char** argv) {
	int i, maxnconn;
	pthread_t tid;

	pthread_mutex_init(&ndone_mutex, NULL);
	pthread_cond_init(&ndone_cond, NULL);

	if (argc < 5) {
		printf("usage: web <#conn> <IP address> <homepage> <file1> <file2> ...");
	}
	maxnconn = atoi(argv[1]);
	nfiles = min((argc - 4), MAXFILES);
	for (i=0; i<nfiles; i++) {
		file[i].f_name = argv[i+4];
		file[i].f_host = argv[2];
		file[i].f_flags = 0;
	}
	printf("nfiles = %d\n", nfiles);

	homepage(argv[2], argv[3]);
	nlefttoconn = nlefttoread = nfiles;
	nconn = 0;

	while(nlefttoread > 0) {
		while(nconn < maxnconn && nlefttoconn > 0) {
			for(i=0; i<nfiles; i++) {
				if (file[i].f_flags == 0)
					break
			}
			if (i == nfiles) {
				printf("nlefttoconn = %d but nothing found", nlefttoconn);
			}
			file[i].f_flags = F_CONNECTING;
			pthread_create(&tid, NULL, &do_get_read, &file[i]);
			file[i].f_tid = tid;
			nconn++;
			nlefttoconn--;
		}

		pthread_mutex_lock(&ndone_mutex);
		while (ndone == 0) {
			pthread_cond_wait(&ndone_cond, &ndone_mutex);
		}
		for (int i=0; i<nfiles; i++) {
			if (file[i].flags & F_DONE) {
				pthread_join(file[i].f_tid, (void**) &file[i].fptr);
				ndone--;
				nconn--;
				nlefttoread--;
			}
		}
		pthread_mutex_unlock(&ndone_mutex);
	}
	pthread_mutex_destroy(&ndone_mutex);
	exit(0);
}

void* do_get_read(void* fptr) {
	int fd, n;
	char line[MAXLINES];

	fd = tcp_connect(fptr->f_host, SERV);
	fptr->f_fd = fd;

	write_get_cmd(fptr);


	for(;;) {
		if ((n = read(fd, line, MAXLINES)) == 0)
			break;
		printf("read %d bytes from %s \n", n, fptr->f_name);
	}
	printf("end-of-line on %s \n", fptr->f_name);
	close(fd);
	fptr->flags = F_DONE;

	pthread_mutex_lock(&ndone_mutex);
	ndone++;
	pthread_cond_signal(&ndone_cond);
	pthread_mutex_unlock(&ndone_mutex);

	return fptr;
}

int tcp_connect(char* host, char* port) {
	struct sockaddr_in servaddr;
	socklen_t len;
	int sockfd, n;

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	inet_pton(AF_INET, host, &servaddr.sin_addr);
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	n = connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr));
	if (n == -1)
		printf("tcp connect error");

	return sockfd;
}

void write_get_cmd(struct file* fptr) {
	int n;
	char line[MAXLINES];
	n = snprintf(line, sizeof(line), GET_CMD, fptr->f_name);
	write(fptr->fd, line, n);
	printf("wrote %d bytes for %s \n", n, fptr->f_name);
	fptr->f_flags = F_READING;
}

void homepage(const char* host, const char* f_name) {
	int fd, n;
	char line[MAXLINES];

	fd = tcp_connect(host, SERV);
	n = snprintf(line, sizeof(line), GET_CMD, f_name);
	write(fd, line, n);

	for(;;) {
		if ((n = read(fd, line, MAXLINES)) == 0)
			break;
		printf("read %d bytes for home page \n", n);
	}
	printf("end-of-line on home page \n");
	close(fd);
}
