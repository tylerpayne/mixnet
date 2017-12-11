#include <mixnet.h>

void public_decrypt(char **plaintext, char *ciphertext, RSA *key, int len)
{
    printf("public decrypting %i bytes\n",len);
    printf("RSA key check: %i\n",RSA_check_key(key));

    *plaintext = (char*)malloc(len);
    int plen = RSA_public_decrypt(len, ciphertext, *plaintext, key, RSA_PKCS1_PADDING);
    *plaintext = (char*)realloc(*plaintext,plen);
    printf("%i bytes of plaintext:\n",plen);
    fwrite(*plaintext,1,plen,stdout);
    printf("\n");
    fflush(stdout);
}
