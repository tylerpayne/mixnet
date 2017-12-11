#include <mixnet.h>

void symmetric_encrypt(char *plaintext, char **ciphertext, BF_KEY *key, char **k, int plen, int *clen)
{
  //  printf("symmetric_encrypting %i bytes\n",plen);

    int len = 128;
    *k = (unsigned char*)malloc(len);
    RAND_bytes(*k,len);
    BF_set_key(key,len,*k);

    int r = plen % 8;
    *clen = (r==0) ? plen : plen + (8-r);
    plaintext = (char*)realloc(plaintext, *clen);
    *ciphertext = (char*)malloc(*clen);
    memset(*ciphertext,0,*clen);
    for (int i = 0; i < *clen; i+=8)
    {
      BF_ecb_encrypt((void*)(plaintext+i), (void*)(*ciphertext+i), key, BF_ENCRYPT);
    }
    //printf("ciphertext: ");
    //fwrite(*ciphertext,sizeof(char),*clen,stdout);
    //printf("\n");
    //fflush(stdout);
}
