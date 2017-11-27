CC=gcc

all:
	$(CC) $(shell ls src/*.c) -Iinclude/ -o mixnet -lcrypto

install: all
	cp mixnet /usr/bin/mixnet
	cp include/mixnet.h /usr/include/mixnet.h
