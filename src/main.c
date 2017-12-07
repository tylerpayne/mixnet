#include <mixnet.h>

int main(int argc, char const *argv[]) {


  KEY = RSA_new();
  FILE *pubkey = fopen("/usr/etc/mixnet/pubkey.pem","r+");
  FILE *privkey = fopen("/usr/etc/mixnet/privkey.pem","r+");
  PEM_read_RSAPublicKey(pubkey, &KEY, NULL,NULL);
  PEM_read_RSAPrivateKey(privkey, &KEY, NULL,NULL);
  printf("RSA key check: %i\n",RSA_check_key(KEY));
  fclose(pubkey);
  fclose(privkey);

  //RSA_print_fp(stdout,KEY,0);

  int len = strlen(argv[1]);
  char *s1 = (char*)malloc(len);
  memcpy(s1,argv[1],len);

  char *s2;
  int clen;
  public_encrypt(s1,&s2,len,&clen);

  return 0;
}
