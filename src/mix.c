#include <mixnet.h>

struct peer
{
  char flag;
  struct sockaddr_in addr;
  char *public_key_str;
  RSA *key;
};

void mix(int fd, struct sockaddr_in sa, char *msg, int len)
{
  printf("mix");
  fflush(stdout);
  int plen = peer_count()-1;
  printf("plen: %i",plen);
  fflush(stdout);
  int *path = (int*)malloc(sizeof(int)*plen);

  for (int i = 0; i < plen; i++)
  {
    path[i] = i;
  }

  BF_KEY key;
  char *cipher, *enckey, *k, *buf;
  int clen, enckey_len;
  int peer_size = (int)sizeof(struct peer);
  buf = (char*)malloc(len+sizeof(struct sockaddr_in));


// innermost layer
  struct peer dummy;
  memset(&dummy,0,peer_size);
  dummy.flag='1';
  struct peer hm1 = *peer_get(path[plen-1]);
  hm1.flag='0';

  buf = realloc(buf,len+peer_size);
  memcpy(buf,(void*)&dummy,peer_size);
  memcpy(buf+peer_size,msg,len);
  symmetric_encrypt(buf,&cipher,&key,&k,len,&clen);
  public_encrypt(k,&enckey,hm1.key,128,&enckey_len);

  msg = realloc(msg,sizeof(int)+enckey_len+clen);
  memcpy(msg,&enckey_len,sizeof(int));
  memcpy(msg+sizeof(int),enckey,enckey_len);
  memcpy(msg+sizeof(int)+enckey_len,cipher,clen);
  len = sizeof(int)+clen+enckey_len;
  free(hm1.public_key_str);

  struct peer h = hm1;

  for (int i = plen-2; i >= 0; i--)
  {
    h = *peer_get(path[i]);
    printf("hm1port: %i\n",ntohs(hm1.addr.sin_port)); fflush(stdout);
    printf("hport: %i\n",ntohs(h.addr.sin_port)); fflush(stdout);
    h.flag = '0';

    buf = realloc(buf,len+peer_size);
    memcpy(buf,(void*)&hm1,peer_size);
    memcpy(buf+peer_size,msg,len);
    symmetric_encrypt(buf,&cipher,&key,&k,len,&clen);
    printf("clen: %i symkey: %s\n",clen,k);
    public_encrypt(k,&enckey,h.key,128,&enckey_len);

    msg = realloc(msg,sizeof(int)+enckey_len+clen);
    memcpy(msg,&enckey_len,sizeof(int));
    memcpy(msg+sizeof(int),enckey,enckey_len);
    memcpy(msg+sizeof(int)+enckey_len,cipher,clen);
    len = sizeof(int)+clen+enckey_len;
    free(h.public_key_str);
  }
  printf("sending %i bytes to: %i\n",len,ntohs(h.addr.sin_port));
  sendto(fd,msg,len,0,(struct sockaddr*)&(h.addr),sizeof(struct sockaddr_in));

  exit(0);
}
