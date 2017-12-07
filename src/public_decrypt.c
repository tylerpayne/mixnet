#include <mixnet.h>

void public_decrypt(char **plaintext, char *ciphertext, int len)
{
    printf("public decrypting %i bytes\n",len);
    printf("RSA key check: %i\n",RSA_check_key(KEY));

    *plaintext = (char*)malloc(len);
    memset(*plaintext,0,len);
    int plen = RSA_public_decrypt(plen, ciphertext, *plaintext, KEY, RSA_NO_PADDING);

    printf("%i bytes of plaintext:\n",plen);
    fwrite(*plaintext,sizeof(char),plen,stdout);
    printf("\n");
    fflush(stdout);
}
