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

  int peer_size = sizeof(struct peer);

// innermost layer

  struct peer hm1;
  memcpy(&hm1,msg,peer_size);

  char *buf = (char*)malloc(len);
  int buf_len = len;
  memcpy(buf,msg,len);

  struct peer h = hm1;

  for (int i = plen-1; i >= 0; i--)
  {
    h = *peer_get(path[i]);
    pack((void**)&msg,&len,hm1,h,buf,buf_len);
    hm1 = h;
    buf = msg;
    buf_len = len;
  }
  printf("sending %i bytes to: %i\n",len,ntohs(h.addr.sin_port));
  fflush(stdout);
  sendto(mixer_fd,msg,len,0,(struct sockaddr*)&(h.addr),sizeof(struct sockaddr_in));
  perror("sent");
  free(buf);
}
