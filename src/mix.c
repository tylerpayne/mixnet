#include <mixnet.h>

struct mix_t
{
  int fd;
  struct sockaddr sa;
  char *msg;
  int len;
};

void *mix(void *mm)
{
  printf("MIX!\n");
  fflush(stdout);
  mix_t m = *((mix_t*)mm);
  int fd = m.fd;
  struct sockaddr sa = m.sa;
  char *msg = m.msg;
  int len = m.len;

  BF_KEY key;
  char *cipher;
  int clen;
  char *k = symmetric_encrypt(msg,&cipher,&key,len,&clen);
  fwrite(k,1,128,stdout);
  printf("\n");
  char *enckey;
  int enckey_len;
  public_encrypt(k,&enckey,128,&enckey_len);
  char *deckey;
  public_decrypt(&deckey,enckey,enckey_len);


  return NULL;
}
