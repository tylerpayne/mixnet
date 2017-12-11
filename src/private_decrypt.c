#include <mixnet.h>

void private_decrypt(char **plaintext, char *ciphertext, RSA *key, int len)
{
    printf("private decrypting %i bytes\n",len);
    printf("RSA key check: %i\n",RSA_check_key(key));

    *plaintext = (char*)malloc(len);
    memset(*plaintext,0,len);
    int plen = RSA_private_decrypt(len,ciphertext,*plaintext,key,RSA_PKCS1_PADDING);
    *plaintext  = (char*)realloc(*plaintext,plen);
    printf("%i bytes of plaintext:\n",plen);
    fwrite(*plaintext,sizeof(char),plen,stdout);
    printf("\n");
    fflush(stdout);
}
