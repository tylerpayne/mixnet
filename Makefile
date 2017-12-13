CC=gcc

.PHONY: build run_test tracker mixnet test kill install uninstall clean

build: mixnet tracker

mixnet:
	$(CC) $(shell ls src/*.c) $(shell ls common/*.c) -Iinclude/ -o mixnet -lcrypto -lpthread


tracker:
	$(CC) $(shell ls tracker_src/*.c) $(shell ls common/*.c) -Iinclude/ -o tracker -lcrypto -lpthread

run_test:
	./tracker start
	./mixnet start -m 5004 -p 5005 -q
	./mixnet start -m 5006 -p 5007 -q
	./mixnet start -m 5000 -p 5001 -q
	python tester.py

kill:
	kill -9 $(shell pidof mixnet tracker)

install: build
	cp mixnet /usr/bin/mixnet
	cp include/mixnet.h /usr/include/mixnet.h

uninstall:
		rm -rf /usr/bin/mixnet
		rm -rf /usr/include/mixnet.h
		rm -rf /usr/etc/mixnet

clean:
	rm /usr/etc/mixnet/mixer*err
	rm /usr/etc/mixnet/mixer*out
	rm /usr/etc/mixnet/peeler*err
	rm /usr/etc/mixnet/peeler*out
	rm /usr/etc/mixnet/peer
	rm mixnet
	rm tracker
