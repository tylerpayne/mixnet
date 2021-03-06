#include <mixnet.h>

struct host
{
  char *ip_addr;
  unsigned short port;
  RSA *key;
};

struct mix_t
{
  int fd;
  struct sockaddr sa;
  char *msg;
  int len;
};

struct mixchain
{
  unsigned char flag;
  char signed_key[16], dest[32];
  int len;
  char body;
};

void *memmem(const void *haystack, size_t hlen, const void *needle, size_t nlen)
{
    int needle_first;
    const void *p = haystack;
    size_t plen = hlen;

    if (!nlen)
        return NULL;

    needle_first = *(unsigned char *)needle;

    while (plen >= nlen && (p = memchr(p, needle_first, plen - nlen + 1)))
    {
        if (!memcmp(p, needle, nlen))
            return (void *)p;

        p++;
        plen = hlen - (p - haystack);
    }

    return NULL;
}

/*
mixchain
- len is length in bytes of body
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
