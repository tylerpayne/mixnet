#include <mixnet.h>

struct peer
{
  char flag;
  struct sockaddr_in addr;
  char *public_key_str;
  RSA *key;
};

void peel(char *msg, int len, int fd)
{
  int enckey_len;
  memcpy(&enckey_len,msg,sizeof(int));
  char *enckey = (char*)malloc(enckey_len);
  char *k;
  memcpy(enckey,msg+sizeof(int),enckey_len);
  private_decrypt(&k,enckey,RSAKEY,enckey_len);
  printf("symkey: %s\n",k);
  fflush(stdout);
  BF_KEY key;
  BF_set_key(&key,128,k);

  char *unwrapped_msg;
  int um_len=0, payload_len=0;
  printf("symdec\n");
  fflush(stdout);
  symmetric_decrypt(&unwrapped_msg,msg+sizeof(int)+enckey_len,&key,&um_len,len-sizeof(int)-enckey_len);
  printf("um_len: %i\n",um_len);
  fflush(stdout);

  struct peer h = *(struct peer*)malloc(sizeof(struct peer));
  memcpy(&h,unwrapped_msg,sizeof(struct peer));
  printf("f=%c next hop: %s:%i\n",h.flag,inet_ntoa(h.addr.sin_addr),ntohs(h.addr.sin_port));
  fflush(stdout);
  payload_len = um_len-sizeof(struct peer);
  printf("payload_len: %i",payload_len);

  printf("fd: %i\n",fd);
  printf("h is null %i\n",&(h.addr)==NULL);


  char *payload = (char*)malloc(payload_len);
  memcpy(payload,unwrapped_msg+sizeof(struct peer),payload_len);
  printf("payload: ");
  fwrite(payload,1,payload_len,stdout);
  fflush(stdout);
  sendto(fd,payload,payload_len,0,(struct sockaddr*)&(h.addr),sizeof(struct sockaddr_in));
  fsync(fd);
  printf("hello2\n");
  perror("sendto");
  fflush(stdout);
  exit(0);
}
