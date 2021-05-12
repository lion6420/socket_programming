#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
	int n, file_fd;
	char buffer[1000];
	file_fd = open("./test.json", O_RDONLY);
	n = read(file_fd, buffer, sizeof(buffer));
	buffer[n] = 0;
	fputs(buffer, stdout);
	return 0;
}
