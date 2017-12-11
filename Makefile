CC=gcc

all:
	$(CC) $(shell ls src/*.c) $(shell ls common/*.c) -Iinclude/ -o mixnet -lcrypto -lpthread

tracker:
	$(CC) $(shell ls _tracker_src/*.c) $(shell ls common/*.c) -Iinclude/ -o tracker -lcrypto -lpthread

install: all
	cp mixnet /usr/bin/mixnet
	cp include/mixnet.h /usr/include/mixnet.h

uninstall:
		rm -rf /usr/bin/mixnet
		rm -rf /usr/include/mixnet.h
		rm -rf /usr/etc/mixnet

clean:
	rm -rf /usr/etc/mixnet/keys
	rm /usr/etc/mixnet/hosts
	rm mixnet
	rm tracker
