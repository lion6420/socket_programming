#include "web.h"

#define extlen 10;

void do_get_cmd(int sockfd) {
	int i, n, file_fd;
	char buffer[MAXLINES];
	char** cmd_arr;
	char method[10], pathname[MAXLINES];
	char extension[10];

	if (n = read(sockfd, buffer, MAXLINES) == 0) {
		printf("client close the connect");
		close(sockfd);
		exit(0);
	}
	else {
		buffer[n] = 0;
		cmd_arr = split_char(buffer);
		// check cmd type
		if (cmd_arr[0] != "GET" || cmd_arr[0] != "get") {
			printf("only support GET method");
		}
		if (file_fd = open(cmd_arr[1], O_RDONLY) == -1) {
			printf("Fail to open the file %c\n", cmd_arr[1]);
		}

		snprintf(extension, 10, )
		snprintf(buffer, MAXLINES, "HTTP/1.1 200 OK\r\n")
	}
}

char** split_char(str, target) {
	int len = strlen(str);
	char* result[len];
	string temp = "";
	int rptr = 0;
	char spliter;
	if (target)
		spliter = target;
	else
		spliter = ' '
	for (int i=0; i<len; i++) {
		if (str[i] == spliter) {
			result[rptr] = temp;
			temp = "";
			rptr++;
		}
		else {
			temp+=str[i];
		}
	}
	return result;
}

char* get_extension(filename) {
	char extension[extlen];
	int len = strlen(filename);
	char* filename_end = filename + len - 1;
	char* sptr = filename_end;
	while (*sptr != '.' && sptr != filename)
		sptr--;
	
	if (sptr != filename || *sptr == '.')sptr++;
	else {
		printf("warning: there is no extension name.");
		extension[0] = 0;
		return extension;
	}
	if ((filename_end-sptr) >= extlen){
		printf("warning: file extension exceed the maximum value %d\n", extlen);
	}
	snprintf(extension, extlen, sptr);
	return extension;
}
