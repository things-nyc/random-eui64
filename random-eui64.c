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
	int fd, iArg;
	unsigned char eui[8];
	unsigned sizeEui, iEui;
	char cSep;

	sizeEui = 8;
	cSep = '-';

	for (iArg = 1; iArg < ac; ++iArg)
		{
		if (strcmp(av[iArg], "-eui48") == 0)
			sizeEui = 6;
		else if (strcmp(av[iArg], "-eui64") == 0)
			sizeEui = 8;
		else if (strcmp(av[iArg], "-colon") == 0)
			cSep = ':';
		else if (strcmp(av[iArg], "-dash") == 0)
			cSep = '-';
		else if (strcmp(av[iArg], "-h") == 0 ||
			 strcmp(av[iArg], "--help") == 0 ||
			 strcmp(av[iArg], "-help") == 0)
			{
			errx(EXIT_SUCCESS, "usage: [-eui48 -eui64 -colon -dash]");
			}
		else
			errx(EXIT_FAILURE, "invalid argument: %s", av[iArg]);
		}

	fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
		{
		perror("can't open /dev/random");
		exit(1);
		}

	if (read(fd, eui, sizeEui) != sizeEui)
		{
		fprintf(stderr, "couldn't read %u bytes\n", sizeEui);
		exit(1);
		}

	eui[0] = (eui[0] & ~1) | 2;
	for (iEui = 0; iEui < sizeEui; ++iEui)
		{
		printf("%02X%c", eui[iEui], iEui == sizeEui - 1 ? '\n' : cSep);
		}

	return 0;
	}
