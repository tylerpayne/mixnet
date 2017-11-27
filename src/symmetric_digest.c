#include <mixnet.h>

void symmetric_digest(char *plaintext, char *ciphertext,
                   int *plen, int *clen,
                   unsigned char direction)
{
    unsigned char *r = (unsigned char*)malloc(128);
    RAND_bytes(r,128);
}
