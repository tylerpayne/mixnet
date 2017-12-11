#include <mixnet.h>

int main(int argc, char const *argv[]) {

  RSA* RSAKEY = RSA_new();
  printf("1\n");
  FILE *pubKEY = fopen("/usr/etc/mixnet/pubkey.pem","r+");
  FILE *privKEY = fopen("/usr/etc/mixnet/privkey.pem","r+");
  printf("2 %i\n",RSAKEY==NULL);
  PEM_read_RSAPublicKey(pubKEY, &RSAKEY, NULL,NULL);
  PEM_read_RSAPrivateKey(privKEY, &RSAKEY, NULL,NULL);
  printf("RSA KEY check: %i\n",RSA_check_key(RSAKEY));
  fclose(pubKEY);
  fclose(privKEY);

  //RSA_print_fp(stdout,KEY,0);

  int len = atoi(argv[1]);
  char *s1 = (char*)malloc(len);
  RAND_bytes(s1,len);
  fwrite(s1,1,len,stdout);
  printf("\n");
  char *s2, *s3;
  int clen;
  private_encrypt(s1,&s2,RSAKEY,len,&clen);
  public_decrypt(&s3,s2,RSAKEY,clen);

  /*int len = strlen(argv[1]);
  char *s1 = (char*)malloc(len);
  memcpy(s1,argv[1],len);

  int clen = RSA_size(KEY);

  char *s2 = (char*)malloc(clen);
  RSA_public_encrypt(len, s1, s2, KEY, RSA_PKCS1_PADDING);
  printf("clen: %i\n",clen);
  fwrite(s2,1,clen,stdout);
  fflush(stdout);
  printf("\n\n");

  char *s3 = (char*)malloc(clen);
  int plen = RSA_private_decrypt(clen,s2,s3,KEY,RSA_PKCS1_PADDING);
  printf("plen: %i\n",plen);
  fwrite(s3,1,plen,stdout);
  fflush(stdout);
  printf("\n");*/

  return 0;
}
