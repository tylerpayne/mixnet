## usage

### setup

````C
$ git clone https://github.com/tylerpayne/mixnet
$ cd mixnet
$ sudo -s
root$ make build
root$ ./mixnet setup <NAME>
````
Replace  `name` with a username.

### start
````C
root$ ./mixnet start [-m] -MIXER_PORT [-p] PEELER_PORT [-q]
````
the mixer server will be running on port `5000` or `MIXER_PORT`, treat this port as a proxy

the peeler server will be running on port `5001` or `PEELER_OUT`

`-q` (quiet) redirects the mixer and peeler processes' `stdout` and `stderr` to files in `/usr/etc/mixnet`


### stop
````C
root$ ./mixnet stop
````

## demo

### tracker
The tracker (akin to a bittorrent tracker) tracks which peers in the mixnet are currently available.

the tracker is started by

````C
root$ ./tracker start
````

### run test
The test uses the local area network to simulate the operation of a mixnet on a wide area network.

First, the tracker server is started. Then several mixnet peers are started on distinct ports. The test program `tester` opens a socket on port `8009` and sends a message `"Hello, world!"` with destination `127.0.0.1:8009` (i.e. itself) through the mixer running on port `5000`. The message is routed through the peers (peeler servers) on the mixnet, achieving anonymity from the message’s recipient.

To run the test

````C
root$ make run_test
````

where

````C
run_test: build tester
	./tracker start -q
	./mixnet start -m 5004 -p 5005 -q
	./mixnet start -m 5006 -p 5007 -q
	./mixnet start -m 5008 -p 5009 -q
	./mixnet start -m 5010 -p 5011 -q
	./mixnet start -m 5000 -p 5001 -q
	./tester
````

Between tests be sure to run

````C
root$ make clean
````
