#include <mixnet.h>

void public_encrypt(char *plaintext, char **ciphertext, int plen, int *clen)
{
    printf("public encrypting %i bytes\n",plen);
    printf("RSA key check: %i\n",RSA_check_key(KEY));

    *clen = RSA_size(KEY);
    *ciphertext = (char*)malloc(*clen);
    memset(*ciphertext,0,*clen);
    RSA_public_encrypt(plen, plaintext, *ciphertext, KEY, RSA_NO_PADDING);

    printf("%i bytes of ciphertext:\n",*clen);
    fwrite(*ciphertext,sizeof(char),*clen,stdout);
    printf("\n");
    fflush(stdout);
}
