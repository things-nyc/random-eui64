/* random-eui64.c	Fri Jul 27 2018 19:59:57 tmm */

/*

Module:  random-eui64.c

Function:
	Generate a random EUI-64 id.

Version:
	V1.02	Fri Jul 27 2018 19:59:57 tmm	Edit level 2

Copyright notice:
	This file copyright (C) 2016, 2018 by

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

   1.02  Fri Jul 27 2018 19:59:57  tmm
	Add options, eui-48 generation, etc.

*/

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/fcntl.h>

int main(int ac, char **av)
	{
	int fd, i;
	unsigned char eui[8];
	unsigned sizeEui;
	char cSep;

	sizeEui = 8;
	cSep = '-';

	for (i = 1; i < ac; ++i)
		{
		if (strcmp(av[i], "-eui48") == 0)
			sizeEui = 6;
		else if (strcmp(av[i], "-eui64") == 0)
			sizeEui = 8;
		else if (strcmp(av[i], "-colon") == 0)
			cSep = ':';
		else if (strcmp(av[i], "-dash") == 0)
			cSep = '-';
		else if (strcmp(av[i], "-h") == 0 ||
			 strcmp(av[i], "--help") == 0 ||
			 strcmp(av[i], "-help") == 0)
			{
			errx(EXIT_SUCCESS, "usage: [-eui48 -eui64 -colon -dash]");
			}
		else
			errx(EXIT_FAILURE, "invalid argument: %s", av[i]);
		}

	fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
		{
		perror("can't open /dev/random");
		exit(1);
		}

	if (read(fd, eui, sizeEui) != sizeEui)
		{
		fprintf(stderr, "couldn't read %zu bytes\n", sizeEui);
		exit(1);
		}

	eui[0] = (eui[0] & ~1) | 2;
	for (i = 0; i < sizeEui; ++i)
		{
		printf("%02X%c", eui[i], i == sizeEui - 1 ? '\n' : cSep);
		}

	return 0;
	}
