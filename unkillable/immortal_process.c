#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>


int main(int argc, char **argv) 
{
	int fd;
	char c;
	char buffer[10];
	int my_pid = getpid();
	char *p = NULL;

	printf("My pid: %d\n", my_pid);
	fd = open("/dev/unkillable", O_RDWR);
	if (fd < 0)
		printf("Error opening /dev/unkillable\n");
	printf("Opened /dev/unkillable\n");
	read(fd, &c, my_pid);
	printf("We are now unkillable!\n");
	read(STDIN_FILENO, buffer, 10);
	printf("exiting on user input...\n");
	return 0;
}
