from socket import *

s = socket(AF_INET,SOCK_DGRAM)
addr = ("127.0.0.1",5000)
s.sendto("Hello, world!", addr)
