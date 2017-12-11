#include <mixnet.h>

void private_encrypt(char *plaintext, char **ciphertext, RSA *key, int plen, int *clen)
{
    printf("private encrypting %i bytes\n",plen);
    printf("RSA key check: %i\n",RSA_check_key(key));
    *clen = RSA_size(key);
    *ciphertext = (char*)malloc(*clen);
    RSA_private_encrypt(plen,plaintext,*ciphertext,key,RSA_PKCS1_PADDING);

    printf("%i bytes of ciphertext:\n",*clen);
    fwrite(*ciphertext,1,*clen,stdout);
    printf("\n");
    fflush(stdout);
}
