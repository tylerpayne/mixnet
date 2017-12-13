#include <mixnet.h>

struct peer
{
  char flag;
  struct sockaddr_in addr;
  char *public_key_str;
  RSA *key;
};

struct peer *peer_get(int idx)
{
  printf("getting host\n");
  FILE *PEER_FILE = fopen("/usr/etc/mixnet/peer","r+");

  fseek(PEER_FILE,0,SEEK_END);
  int size = ftell(PEER_FILE);
  rewind(PEER_FILE);

  char *peer = (char*)malloc(size);
  fread(peer,1,size,PEER_FILE);

  int c = 0, tz = size;
  char *comma = peer;

  while (c < idx)
  {
    comma = memmem(comma,tz,",",1)+1;
    tz = peer - comma;
    c+=1;
  }

  if (comma==NULL) return NULL;
  printf("comma not null\n");
  fflush(stdout);

  struct peer *h = (struct peer *)malloc(sizeof(struct peer));
  memcpy((void*)h,comma,sizeof(struct peer));

  printf("4\n");
  fflush(stdout);

  h->public_key_str = (char* )malloc(2048+1024);
  printf("4.5\n"); fflush(stdout);
  memcpy(h->public_key_str,comma+sizeof(struct peer),2048+0124);
  BIO *membuf = BIO_new_mem_buf(h->public_key_str,2048+1024);
  perror("BIO");
  printf("got host with port: %i\npublic key: %s\n\n",ntohs(h->addr.sin_port),h->public_key_str);
  fflush(stdout);

  RSA *key = RSA_new();
  if (PEM_read_bio_RSAPublicKey(membuf,&key,NULL,NULL)==NULL) printf("ERROR! NO PUBKEY\n");
  h->key = key;

  BIO_free(membuf);
  fclose(PEER_FILE);
  return h;
}
