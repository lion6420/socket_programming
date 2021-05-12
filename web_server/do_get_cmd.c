#include "web.h"

#define extlen 10

char** split_char(char*, char);
char* get_extension(char*);

void do_get_cmd(int sockfd) {
	int i, n, file_fd;
	char buffer[MAXLINES];
	char** cmd_arr;
	char method[10], pathname[MAXLINES];
	char* extension;

	if ((n = read(sockfd, buffer, MAXLINES)) == 0) {
		printf("Client close the connection");
		close(sockfd);
		exit(0);
	}
	else {
		buffer[n] = 0;
		cmd_arr = split_char(buffer, (char)0);
		printf("%s\n", cmd_arr[0]);
		printf("%s\n", cmd_arr[1]);
		printf("%s\n", cmd_arr[2]);
		// check cmd type
		if (cmd_arr[0] != "GET" || cmd_arr[0] != "get") {
			printf("Only support GET method\n");
		}
		if (file_fd = open(cmd_arr[1], O_RDONLY) == -1) {
			printf("Fail to open the file %c\n", cmd_arr[1]);
		}
		extension = get_extension(cmd_arr[1]);

		snprintf(buffer, MAXLINES, "HTTP/1.1 200 OK\r\nContent-Type: %s\r\n\r\n", extension);
		write(sockfd, buffer, sizeof(buffer));
		n = read(file_fd, buffer, sizeof(buffer));
		buffer[n] = 0;
		fputs(buffer, stdout);
		write(sockfd, buffer, n);
	}
	free(cmd_arr);
	free(extension);
	close(sockfd);
	exit(0);
}

char** split_char(char* str, char target) {
	int len = strlen(str);
	char** result = (char**) malloc(sizeof(str));
	char temp[MAXLINES];
	char* temp_ptr = temp;
	int rptr = 0;
	char spliter;
	if (target)
		spliter = target;
	else
		spliter = ' ';
	for (int i=0; i<len; i++) {
		if (int(str[i]) == int(spliter)) {
			*temp_ptr = 0;
			strcpy(result[rptr], temp);
			temp_ptr = temp;
			rptr++;
		}
		else {
			*temp_ptr = str[i];
			temp_ptr++;
		}
	}
	strcpy(result[rptr], temp);
	return result;
}

char* get_extension(char* filename) {
	char* extension = (char*) malloc(extlen*sizeof(char));
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
