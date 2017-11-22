#include <mixnet.h>

const char *HOST_FILE_PATH = "/etc/mixnet/hosts";
const char *PID_FILE_PATH = "/etc/mixnet/pid";
const char *PKEY_FILE_PATH = "/etc/mixnet/key.pem";
char MIXNET_SERVER_ADDR[32];
int MIXNET_SERVER_PORT = 5001;


struct mixchain
{
  unsigned char flag;
  char signed_key[16], dest[32];
  int len;
  char *body;
};

/*
mixchain
- len is length in bytes of ciphertext
if (flag & 0b10) then
 - signed_key is a 16 byte blowfish key encrypted by your public RSA key.
  if (flag & 0b1) then
    - plaintext is a http payload, deliver it
  else
    - decrypt signed_key to key
    - decode ciphertext using key to plaintext
    - cast plaintext to a mixchain structure, call it new_mixchain.
    - send new_mixchain to new_mixchain.dest
else
 - create a blowfish key, digest body, sign the blowfish key with your private RSA key and return to sender
*/
