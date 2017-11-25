#ifndef _MIXNET_H_
#define _MIXNET_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

const char *HOST_FILE_PATH;
const char *PID_FILE_PATH;
const char *PKEY_FILE_PATH;

typedef struct mixchain mixchain;

void mn_error(char *err);
void handle_sigchild(int sig);

void setup(char *name);
void start();
void stop();

void mixer(int fd, struct sockaddr sa);
void peeler(int fd, struct sockaddr sa);

int create_socket(int domain, int type, char *ip_addr, int port, struct sockaddr *saddr);

#endif
