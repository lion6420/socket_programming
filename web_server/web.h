#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string>
#include <cstring>
#include <fcntl.h>
#include <sys/stat.h>

#define MAXLINES 4096
#define SERV_PORT 8090

void do_get_cmd(int);
