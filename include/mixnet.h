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

unsigned char verbose;
char *MIXNET_PATH, *localhost, *tracker_addr;
unsigned short  mixer_port, peeler_port, tracker_port;
int mixer_fd,peeler_fd,tracker_fd;
struct sockaddr tracker_sa;

int NHOSTS;

typedef struct mixchain mixchain;
typedef struct mix_t mix_t;
struct peer;

void peer_add(struct sockaddr_in from, char *pubkey, int len);
void peer_remove(struct sockaddr_in from);
struct peer *peer_get(int idx);
struct peer *peer_find(struct sockaddr_in addr);
int peer_count();

void *memmem(const void *haystack, size_t hlen, const void *needle, size_t nlen);

void mn_error(char *err);
void handle_sigchild(int sig);

void handle_mixer_sigkill(int sig);
void handle_peeler_sigkill(int sig);

int create_socket(int domain, int type, char *ip_addr, int port, struct sockaddr *saddr);

void setup(char *name);
void start();
void stop();

FILE *mixer_out, *mixer_err;
void mixer(int fd, struct sockaddr sa);
void mix(int fd, struct sockaddr_in sa, char *msg, int len);

FILE *peeler_out, *peeler_err;
void peeler(int fd, struct sockaddr sa);
void peel(char *msg, int len, int fd);

RSA *generate_rsa_key();
RSA *RSAKEY;

void public_encrypt(char *plaintext, char **ciphertext, RSA *key, int plen, int *clen);
void private_decrypt(char **plaintext, char *ciphertext, RSA *key, int len);

void private_encrypt(char *plaintext, char **ciphertext, RSA *key, int plen, int *clen);
void public_decrypt(char **plaintext, char *ciphertext, RSA *key, int len);

void symmetric_encrypt(char *plaintext, char **ciphertext, BF_KEY *key, char **k, int plen, int *clen);
void symmetric_decrypt(char **plaintext, char *ciphertext, BF_KEY *key, int *plen, int clen);

#endif
