#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <linux/if_tun.h>


int main(int argc, char **argv)
{
	int tun_fd, nread, err;
	char buffer[1500];
	struct ifreq ifr;
	char *clonedev = "/dev/net/tun";

	if ((tun_fd = open(clonedev, O_RDWR)) < 0) {
		printf("get tun failed\n");
		return -1;
	}
	memset(&ifr, 0, sizeof(ifr));
	ifr.ifr_flags = (IFF_TUN | IFF_NO_PI);
	
	if ((err = ioctl(tun_fd, TUNSETIFF, (void *)&ifr)) < 0) {
		close(tun_fd);
		printf("get ifreq failed : %d\n", err);
		return err;
	}

	printf("Open tun/tap device : %s for reading ... \n", ifr.ifr_name);

	while (1) {
		nread = read(tun_fd, buffer, sizeof(buffer));
		if (nread < 0) {
			perror("Reading from interface");
			close(tun_fd);

			exit(1);
		}

		printf("Read %d bytes from tun/tap device\n", nread);
		printf("Read buffer:\n %s\n", buffer);
	}

	return 0;
}

