CC=gcc

all:
	$(CC) $(shell ls src/*.c) -Iinclude/ -o mixnet -lcrypto
