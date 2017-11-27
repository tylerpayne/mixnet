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
#include <sys/stat.h>
#include <signal.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/bn.h>
#include <openssl/pem.h>
#include <openssl/rand.h>

const char *HOST_FILE_PATH;
const char *PID_FILE_PATH;
const char *PKEY_FILE_PATH;

typedef struct mixchain mixchain;
unsigned char ENCODE;
unsigned char DECODE;

void mn_error(char *err);
void handle_sigchild(int sig);
int create_socket(int domain, int type, char *ip_addr, int port, struct sockaddr *saddr);

void setup(char *name);
void start();
void stop();

FILE *mixer_out, *mixer_err;
void mixer(int fd, struct sockaddr sa);
mixchain* mix(int fd, struct sockaddr sa, char *msg, int len);

FILE *peeler_out, *peeler_err;
void peeler(int fd, struct sockaddr sa);
void peel(mixchain *chain);

RSA *KEY;

RSA *generate_rsa_key();

void public_digest(char *plaintext, char *ciphertext,
                   int *plen, int *clen,
                   unsigned char direction);

void private_digest(char *plaintext, char *ciphertext,
                   int *plen, int *clen,
                   unsigned char direction);

void symmetric_digest(char *plaintext, char *ciphertext,
                   int *plen, int *clen,
                   unsigned char direction);


#endif
