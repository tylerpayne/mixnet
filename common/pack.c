#include <mixnet.h>

struct peer
{
  char flag;
  struct sockaddr_in addr;
  char *public_key_str;
  RSA *key;
};

void pack(void** bytes, int* bytes_len, struct peer last_hop, struct peer next_hop, char *msg, int msg_len)
{
  printf("packing %i bytes long message: ",msg_len);
  fwrite(msg,1,msg_len,stdout);
  printf("\n");
  fflush(stdout);
  BF_KEY key;
  int peer_size = sizeof(struct peer);

  char *cipher, *enckey, *k, *buf;
  int clen, enckey_len;

  buf = malloc(msg_len+peer_size+sizeof(int));
  memcpy(buf,&last_hop,peer_size);
  memcpy(buf+peer_size,&msg_len,sizeof(int));
  memcpy(buf+peer_size+sizeof(int),msg,msg_len);

  symmetric_encrypt(buf,&cipher,&key,&k,msg_len+peer_size+sizeof(int),&clen);
  public_encrypt(k,&enckey,next_hop.key,128,&enckey_len);

  *bytes_len = sizeof(int)+enckey_len+clen;
  *bytes = malloc(*bytes_len);

  memcpy(*bytes,&enckey_len,sizeof(int));
  memcpy(*bytes+sizeof(int),enckey,enckey_len);
  memcpy(*bytes+sizeof(int)+enckey_len,cipher,clen);
  printf("7\n");fflush(stdout);

}
