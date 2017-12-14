CC=gcc

.PHONY: build tester run_test tracker mixnet test kill install uninstall clean

build: mixnet tracker

mixnet:
	$(CC) $(shell ls src/*.c) $(shell ls common/*.c) -Iinclude/ -o mixnet -lcrypto

tracker:
	$(CC) $(shell ls tracker_src/*.c) $(shell ls common/*.c) -Iinclude/ -o tracker -lcrypto

tester:
	$(CC) $(shell ls tester_src/*.c) $(shell ls common/*.c) -Iinclude/ -o tester -lcrypto

run_test: build tester
	./tracker start -q
	./mixnet start -m 5004 -p 5005 -q
	./mixnet start -m 5006 -p 5007 -q
	./mixnet start -m 5008 -p 5009 -q
	./mixnet start -m 5010 -p 5011 -q
	./mixnet start -m 5000 -p 5001 -q
	./tester

kill:
	kill -9 $(shell pidof mixnet tracker)

install: build
	cp mixnet /usr/bin/mixnet
	cp include/mixnet.h /usr/include/mixnet.h

uninstall:
		rm -rf /usr/bin/mixnet
		rm -rf /usr/include/mixnet.h
		rm -rf /usr/etc/mixnet

clean: kill
	rm /usr/etc/mixnet/mixer*err
	rm /usr/etc/mixnet/mixer*out
	rm /usr/etc/mixnet/peeler*err
	rm /usr/etc/mixnet/peeler*out
	rm /usr/etc/mixnet/peer
	rm mixnet
	rm tracker
