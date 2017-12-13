#include <mixnet.h>

void private_encrypt(char *plaintext, char **ciphertext, RSA *key, int plen, int *clen)
{
    *clen = RSA_size(key);
    *ciphertext = (char*)malloc(*clen);
    RSA_private_encrypt(plen,plaintext,*ciphertext,key,RSA_PKCS1_PADDING);

    printf("private encrypted %i bytes plaintext: \" ",plen);
    fwrite(plaintext,1,plen,stdout);
    printf("\"\n to %i bytes ciphertext \"",*clen);
    fwrite(*ciphertext,1,*clen,stdout);
    printf("\"\n");
    fflush(stdout);
}
