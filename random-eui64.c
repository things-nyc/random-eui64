#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/fcntl.h>

int main(int ac, char **av)
	{
	int fd, i;
	unsigned char eui[8];
	
	fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
		{
		perror("can't open /dev/random: ");
		exit(1);
		}	

	if (read(fd, eui, sizeof(eui)) != sizeof(eui))
		{
		fprintf(stderr, "couldn't read %zu bytes\n", sizeof(eui));
		exit(1);
		}

	eui[0] = (eui[0] & ~1) | 2;
	for (i = 0; i < sizeof(eui); ++i)
		{
		printf("%02X%c", eui[i], i == sizeof(eui)-1 ? '\n' : '-');
		}

	return 0;
 
	}
