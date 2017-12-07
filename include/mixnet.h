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
#include <pthread.h>
#include <openssl/blowfish.h>
#include <time.h>


typedef struct mixchain mixchain;
typedef struct mix_t mix_t;

void mn_error(char *err);
void handle_sigchild(int sig);
int create_socket(int domain, int type, char *ip_addr, int port, struct sockaddr *saddr);

void setup(char *name);
void start();
void stop();

FILE *mixer_out, *mixer_err;
void mixer(int fd, struct sockaddr sa);
void *mix(void *m);

FILE *peeler_out, *peeler_err;
void peeler(int fd, struct sockaddr sa);
void peel(mixchain *chain);

RSA *KEY;

RSA *generate_rsa_key();

void public_encrypt(char *plaintext, char **ciphertext, int plen, int *clen);
void public_decrypt(char **plaintext, char *ciphertext, int len);

void private_digest(char *plaintext, char *ciphertext, int *plen, int *clen, unsigned char direction);

char *symmetric_encrypt(char *plaintext, char **ciphertext, BF_KEY *key, int plen, int *clen);
void symmetric_decrypt(char **plaintext, char *ciphertext, BF_KEY *key, int clen);


#endif
