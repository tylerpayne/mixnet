#include <mixnet.h>

struct peer
{
  char flag;
  struct sockaddr_in addr;
  char *public_key_str;
  RSA *key;
};

void unpack(void** bytes, int* bytes_len, struct peer **next_hop, char *msg, int msg_len)
{
  printf("unpacking\n");
  BF_KEY key;
  int peer_size = sizeof(struct peer);
  char *cipher, *enckey, *k, *buf;
  int clen, enckey_len;

  memcpy(&enckey_len,msg,sizeof(int));

  enckey = (char*)malloc(enckey_len);
  memcpy(enckey,msg+sizeof(int),enckey_len);
  int k_len;
  private_decrypt(&k,enckey,RSAKEY,&k_len,enckey_len);

  BF_set_key(&key,k_len,k);

  char *unwrapped_msg;
  int um_len=0;
  clen = msg_len - sizeof(int) - enckey_len;
  symmetric_decrypt(&unwrapped_msg,msg+sizeof(int)+enckey_len,&key,&um_len,clen);

  *next_hop = (struct peer *)malloc(peer_size);
  memcpy(*next_hop,(void*)unwrapped_msg,peer_size);
  (*next_hop)->public_key_str = NULL;
  (*next_hop)->key = NULL;

  memcpy(bytes_len,unwrapped_msg+peer_size,sizeof(int));
  *bytes = (char*)malloc(*bytes_len);
  memcpy(*bytes,unwrapped_msg+peer_size+sizeof(int),*bytes_len);
}
