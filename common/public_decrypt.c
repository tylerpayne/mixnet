#include <mixnet.h>

void public_decrypt(char **plaintext, char *ciphertext, RSA *key, int *plen, int clen)
{
    *plaintext = (char*)malloc(clen);
    *plen = RSA_public_decrypt(clen, ciphertext, *plaintext, key, RSA_PKCS1_PADDING);
    *plaintext = (char*)realloc(*plaintext,*plen);

    printf("public decrypted %i bytes ciphertext: \" ",clen);
    fwrite(ciphertext,1,clen,stdout);
    printf("\"\n to %i bytes plaintext \"",*plen);
    fwrite(*plaintext,1,*plen,stdout);
    printf("\"\n");
    fflush(stdout);
}
