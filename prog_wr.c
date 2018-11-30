#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <limits.h>
#include <fcntl.h>

#define FIFO_NAME "name_pipe"
#define b_size 1024 //размер буфера

int main()
{
	int pipe_fd;
	int res;
	int in, nread;
	int open_mode = O_WRONLY;
	char buffer[b_size+1];

	if (access(FIFO_NAME, F_OK) == -1) {
		res = mkfifo(FIFO_NAME, 0777);
		if (res != 0) {
			fprintf(stderr, "could not create fifo %s\n", FIFO_NAME);
			exit(EXIT_FAILURE);
		}
	}

	printf("process %d opening FIFO O_WRONLY\n", getpid());
	pipe_fd = open(FIFO_NAME, open_mode);
	printf("process %d result %d\n", getpid(), pipe_fd);
	in = open("film.mkv", O_RDONLY);

	if (pipe_fd != -1) {
		while((nread = read(in, buffer, b_size)) > 1) {
			res = write(pipe_fd, buffer, b_size);
			if (res == -1) {
				fprintf(stderr, "write error on pipe\n");
				exit(EXIT_FAILURE);
			}
		}
		(void)close(pipe_fd);
	}
	else {
		exit(EXIT_FAILURE);
	}
	printf("process %d finished\n", getpid());
	exit(EXIT_SUCCESS);
}