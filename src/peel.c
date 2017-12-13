#include <mixnet.h>

struct peer
{
  char flag;
  struct sockaddr_in addr;
  char *public_key_str;
  RSA *key;
};

void peel(char *msg, int len, int fd, struct sockaddr_in from)
{
  struct peer *h;
  char *payload;
  int payload_len;

  unpack((void**)&payload,&payload_len,&h,msg,len);
  printf("payload: ");
  fwrite(payload,1,payload_len,stdout);
  printf("\n");
  printf("sending %i bytes to: %s:%i\n",payload_len,inet_ntoa(h->addr.sin_addr),ntohs(h->addr.sin_port));
  if (h->flag == '1')
  {
    payload = payload+sizeof(struct peer);
    payload_len = payload_len - sizeof(struct peer);
  }
  sendto(fd,payload,payload_len,0,(struct sockaddr*)&(h->addr),sizeof(struct sockaddr_in));
  perror("sendto");
  fflush(stdout);
  //exit(0);
}
