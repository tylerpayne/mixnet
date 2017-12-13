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
mixer running on port 5000 or `MIXER_PORT`, treat this port as a proxy
peeler running on port 5001 or `PEELER_OUT`
(quiet) `-q` redirects mixer and peeler `stdout` and `stderr` to files in /usr/etc/mixnet

### stop
````C
root$ ./mixnet stop
````

## demo

### tracker
The tracker (akin to a bittorrent tracker and running publicly for a normally functioning mixnet network) tracks which peers in the mixnet are currently available.

the tracker is started by

````C
root$ ./tracker start
````

### run test
The test uses the local area network to simulate the operation of a mixnet on a wide area network. 

First, the tracker server is started. Then several mixnet peers are started on distinct ports. When a locally generated message (e.g. HTTP request) is sent to any MIXER_PORT, the message is routed through the peers on the mixnet, achieving anonymity from the message’s recipient (presumably not a member of the mixnet). The recipient’s response is also routed through the mixnet. 

For this test a simple python script sends an HTTP GET Request for www.google.com to 5000 and prints the response.

To run the test

````C
root$ make run_test
````

where

````C
run_test: build
	./tracker start
	./mixnet start -m 5004 -p 5005 -q
	./mixnet start -m 5006 -p 5007 -q
	./mixnet start -m 5000 -p 5001 -q
	python tester.py
````

Between tests run 

````C
root$ make clean
````
