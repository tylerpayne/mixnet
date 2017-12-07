#include <mixnet.h>

void symmetric_decrypt(char **plaintext, char *ciphertext, BF_KEY *key, int clen)
{
    //printf("symmetric_decrypt %i bytes\n",clen);
    *plaintext = (char*)malloc(clen);
    for (int i=0; i < clen; i+=8)
    {
      BF_ecb_encrypt((void*)(ciphertext+i), (void*)(*plaintext+i), key, BF_DECRYPT);
    }
    //printf("plaintext: ");
    //fwrite(*plaintext,1,clen,stdout);
    //printf("\n");
    //fflush(stdout);
}
