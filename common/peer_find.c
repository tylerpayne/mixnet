#include <mixnet.h>

struct peer
{
  char flag;
  struct sockaddr_in addr;
  char *public_key_str;
  RSA *key;
};

struct peer *peer_find(struct sockaddr_in addr)
{
  printf("finding host\n");
  FILE *PEERS_FILE = fopen("/usr/etc/mixnet/peers","r+");

  fseek(PEERS_FILE,0,SEEK_END);
  int size = ftell(PEERS_FILE);
  rewind(PEERS_FILE);

  char *peers = (char*)malloc(size);
  fread(peers,1,size,PEERS_FILE);
  fflush(PEERS_FILE);
  fclose(PEERS_FILE);

  char *found = memmem(peers,size,&addr,sizeof(struct sockaddr_in));
  printf("found is null: %i\n",found==NULL);
  fflush(stdout);
  struct peer *h = (struct peer *)malloc(sizeof(struct peer));
  memcpy(h,found,sizeof(struct sockaddr_in) + 2048+1024);
  printf("hello?\n");
  fflush(stdout);

  BIO *membuf = BIO_new_mem_buf(h->public_key_str,2048+1024);

  RSA *key = RSA_new();
  PEM_read_bio_RSAPublicKey(membuf,&key,NULL,NULL);
  h->key = key;

  BIO_free(membuf);

  return h;
}
