CC=gcc

all:
	$(CC) $(shell ls src/*.c) -Iinclude/ -o mixnet -lcrypto -lpthread

install: all
	cp mixnet /usr/bin/mixnet
	cp include/mixnet.h /usr/include/mixnet.h

uninstall:
		rm -rf /usr/bin/mixnet
		rm -rf /usr/include/mixnet.h
		rm -rf /usr/etc/mixnet
