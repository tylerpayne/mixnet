#include <mixnet.h>

void public_encrypt(char *plaintext, char **ciphertext, RSA *key, int plen, int *clen)
{
    printf("public encrypting %i bytes\n",plen);
    printf("RSA key check: %i\n",RSA_check_key(key));
    *clen = RSA_size(key);
    printf("3\n");
    fflush(stdout);
    *ciphertext = (char*)malloc(*clen);
    printf("1\n");
    fflush(stdout);
    RSA_public_encrypt(plen, plaintext, *ciphertext, key, RSA_PKCS1_PADDING);
    printf("2\n");
    printf("%i bytes of ciphertext:\n",*clen);
    fwrite(*ciphertext,sizeof(char),*clen,stdout);
    printf("\n");
    fflush(stdout);
}
