#include <mixnet.h>

RSA *generate_rsa_key()
{
  printf("1\n");
  RSA *key = RSA_new();
  BIGNUM *e = BN_new();
  printf("2\n");
  BN_dec2bn(&e,"17");
  printf("3\n");
  RSA_generate_key_ex(key, 1024, e, NULL);

  FILE *pubkey = fopen("/etc/mixnet/pubkey.pem","w+");
  FILE *privkey = fopen("/etc/mixnet/privkey.pem","w+");
  printf("4\n");
  PEM_write_RSAPublicKey(pubkey, key);
  printf("5\n");
  PEM_write_RSAPrivateKey(privkey, key, NULL, NULL, 0, NULL, NULL);
  fclose(pubkey);
  fclose(privkey);
  return key;
}
