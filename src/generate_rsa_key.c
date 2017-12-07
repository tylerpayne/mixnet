#include <mixnet.h>

RSA *generate_rsa_key()
{
  RSA *key = RSA_new();
  BIGNUM *e = BN_new();
  BN_dec2bn(&e,"17");
  RSA_generate_key_ex(key, 1024, e, NULL);

  FILE *pubkey = fopen("/usr/etc/mixnet/pubkey.pem","w+");
  FILE *privkey = fopen("/usr/etc/mixnet/privkey.pem","w+");
  printf("Generated RSA Keypair\n");
  PEM_write_RSAPrivateKey(privkey, key, NULL, NULL, NULL, NULL, NULL);
  PEM_write_RSAPublicKey(pubkey, key);
  fclose(pubkey);
  fclose(privkey);
  return key;
}
