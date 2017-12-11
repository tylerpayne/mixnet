#include <mixnet.h>

void peel(char *msg, int len, int fd)
{

  char *enck = (char*)malloc(256);
  char *k;
  memcpy(enck,msg,256);
  private_decrypt(&k,enck,RSAKEY,256);

  BF_KEY key;
  BF_set_key(&key,128,k);
  char *unwrapped_msg;
  symmetric_decrypt(&unwrapped_msg,msg+256,&key,len-256);

  //printf("recovered: %s\n",unwrapped_msg);

}
