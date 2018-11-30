#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

// 639page!!!

#define PIPE_BUF
#define FIFO_NAME "name_pipe"
#define b_size 1024 //размер буфера

int main()
{
	int pipe_fd, out;
	int res;
	int open_mode = O_RDONLY;
	char buffer[b_size+1];

	memset(buffer, '\0', sizeof(buffer));
	out = open("film_new.mkv", O_WRONLY | O_CREAT, S_IRUSR|S_IWUSR);

	printf("process %d opening FIFO O_RDONLY\n", getpid());
	pipe_fd = open(FIFO_NAME, open_mode);
	printf("process %d result %d\n", getpid(), pipe_fd);

	if (pipe_fd != -1) {
		do {
			res = read(pipe_fd, buffer, b_size);
			write(out, buffer, res);
		} while (res > 0);
		(void)close(pipe_fd);
	}
	else {
		exit(EXIT_FAILURE);
	}
	printf("process %d finished\n", getpid());
	exit(EXIT_SUCCESS);
}