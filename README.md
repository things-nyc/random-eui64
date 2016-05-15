# random-eui64
Simple program for generating a locally-administered EUI, following the rules
given in 
[IEEE 802](http://standards.ieee.org/getieee802/download/802-2014.pdf) 
section 8.2.

A random EUI-64 may be useful for experimenters who are prototyping devices,
and don't have access to a pool of globally-administered addresses.

You'll have to judge whether you want to use a random ID. However, the definition of EUI-64 allows for this. 

Section 8.2 describes the u/l bit (bit 1) of byte 0 of EUI-64. If you set that bit, you have a "locally administered address". Bit 0 always has to be zero for addresses. So a legitimate way of generating a random address, with very low probability of collision, is to generate 8 random bytes, then set bit 1 of byte 0, clear bit 0 of byte 0. On Ubuntu, this simple program will do what you need.

random-eui64 uses data from /dev/random to generate a suitable random address
and prints it out in the canonical format. Becuase it uses /dev/random, it may
delay indefinitely if your system doesn't have enough available entropy.

Example:
```
$ random-eui64
4E-D9-09-C5-5E-57-B9-F6
```
## Building
There's no makefile, but the default rules of make can be used.
```
$ make random-eui64
cc     random-eui64.c   -o random-eui64
```

