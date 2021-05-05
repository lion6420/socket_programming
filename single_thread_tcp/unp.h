#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> // basic socket definitions
#include <netinet/in.h> // sockaddr_in{} and other Internet definitions
#include <arpa/inet.h> // inet(3) functions
#include <errno.h>
#include <unistd.h>
#include <pthread.h>

#define LISTENQ 8
#define MAXLINE 4096

// server addr
#define SERV_PORT 8090

#define SA struct sockaddr
void str_echo(int);
void str_cli(FILE*, int);
