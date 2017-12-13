#include <mixnet.h>

void public_encrypt(char *plaintext, char **ciphertext, RSA *key, int plen, int *clen)
{
    *clen = RSA_size(key);
    fflush(stdout);
    *ciphertext = (char*)malloc(*clen);
    fflush(stdout);
    RSA_public_encrypt(plen, plaintext, *ciphertext, key, RSA_PKCS1_PADDING);

    printf("public encrypted %i bytes plaintext: \" ",plen);
    fwrite(plaintext,1,plen,stdout);
    printf("\"\n to %i bytes ciphertext \"",*clen);
    fwrite(*ciphertext,1,*clen,stdout);
    printf("\"\n");
    fflush(stdout);
}
