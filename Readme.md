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
The test uses the local area network to simulate the operation of a mixnet on a wide area network. First, the tracker server is started, then several mixnet peers are started on distinct ports. Finally a 
