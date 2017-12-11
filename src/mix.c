#include <mixnet.h>

struct mix_t
{
  int fd;
  struct sockaddr_in sa;
  char *msg;
  int len;
};

struct host
{
  char ip_addr[32];
  unsigned short port;
  RSA *key;
};

void *mix(void *mm)
{
  printf("MIX!\n");
  mix_t m = *((mix_t*)mm);
  int fd = m.fd;
  struct sockaddr_in sa = m.sa;

  int len = m.len;
  char *msg = (char*)malloc(len);
  memcpy(msg,m.msg,len);

  int plen = 2;
  int path[2] = {0,1};


  host *hosts[2];

  BF_KEY key;
  char *cipher, *enckey, *k, *buf;
  int clen, enckey_len;
  buf = (char*)malloc(len+64);
  for (int i = 0; i < plen; i++)
  {
    hosts[i] = hosts_get(path[i]);
    host *h = hosts[i];
    if (i > 0)
    {
      sprintf(buf,"%s:%i;%s",h->ip_addr,h->port,msg);
    } else
    {
      sprintf(buf,"%s",msg);
    }

    symmetric_encrypt(buf,&cipher,&key,&k,len+64,&clen);
    printf("key: %s\n",k);
    public_encrypt(k,&enckey,h->key,128,&enckey_len);

    printf("enckey_len: %i\n",enckey_len);
    buf = realloc(buf,clen+enckey_len);
    memset(buf,0,clen+enckey_len);
    memcpy(buf,enckey,enckey_len);
    memcpy(buf+enckey_len,cipher,clen);
  }
  struct sockaddr_in hop;
  hop.sin_family = AF_INET;
  inet_pton(AF_INET,&(hosts[plen-1]->ip_addr[0]),&(hop.sin_addr));
  hop.sin_port = htons(hosts[plen-1]->port);
  printf("sending %i bytes %s\n",enckey_len+clen,buf);
  sendto(fd,buf,clen+enckey_len,0,(struct sockaddr*)&hop,sizeof(struct sockaddr_in));
  return NULL;
}
