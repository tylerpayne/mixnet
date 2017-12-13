#include <mixnet.h>

struct peer
{
  char flag;
  struct sockaddr_in addr;
  char *public_key_str;
  RSA *key;
};

void peer_add(struct sockaddr_in from, char *pubkey, int len)
{
  FILE *PEERS_FILE = fopen("/usr/etc/mixnet/peer","ab");

  struct peer h;
  h.flag = '0';
  h.addr=from;
  from.sin_addr.s_addr = inet_addr("127.0.0.1");
  h.key = NULL;
  h.public_key_str = NULL;

  fwrite(&h,1,sizeof(struct peer),PEERS_FILE);
  fwrite(pubkey,1,len,PEERS_FILE);
  fwrite(",",1,1,PEERS_FILE);

  fflush(PEERS_FILE);
  fclose(PEERS_FILE);

}
