#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char const *argv[]) {
	
	printf("Some Initial Message...\n");

	int s = fork();
	if (!s) {fork();}

	if (!s) { //I am the child

		printf("My pid is %i!\n", getpid());

		int fd;

		if( (fd = open("/dev/urandom", O_RDONLY)) == -1) {
			printf("Error opening /dev/urandom: %s\n", strerror(errno));
		}

		unsigned char * x  = malloc(sizeof(char));

		if (read(fd, x, 1) == -1) {
			printf("Error reading from /dev/urandom: %s\n", strerror(errno));
		}

		if (close(fd) == -1) {
			printf("Error closing /dev/urandom: %s\n", strerror(errno));
		}

		printf("(%i) Good Night (%i)\n", getpid(), *x % 16 + 5);

		sleep(*x % 16 + 5);

		printf("(%i): I have woken up\n", getpid());

	} else {
		
		int status;
		
		printf("My child (%i) has woken up\n", wait(&status));
	}
	
	return 0;
}