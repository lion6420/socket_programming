#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SA struct sockaddr
#define MAXLINE 4096
#define SERV_PORT 8090

void dg_cli(FILE*, int, struct sockaddr*, socklen_t);
void dg_echo(int, struct sockaddr*, socklen_t);
