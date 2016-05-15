/* random-eui64.c	Sat May 14 2016 20:14:09 tmm */

/*

Module:  random-eui64.c

Function:
	Generate a random EUI-64 id.

Version:
	V1.00	Sat May 14 2016 20:14:09 tmm	Edit level 1

Copyright notice:
	This file copyright (C) 2016 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	This code is released under the MIT license; see file named LICENSE in 
	the same directory as this file.
 
Author:
	Terry Moore, MCCI Corporation	May 2016

Revision history:
   1.00  Sat May 14 2016 20:14:09  tmm
	Module created.

*/

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
