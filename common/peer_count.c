#include <mixnet.h>

int peer_count()
{
  printf("counting peers\n");
  fflush(stdout);

  FILE *PEER_FILE = fopen("/usr/etc/mixnet/peer","r+");
  fseek(PEER_FILE,0,SEEK_END);
  int sz = ftell(PEER_FILE);
  rewind(PEER_FILE);

  printf("1 %i\n",sz);
  fflush(stdout);

  char *buf = (char*)malloc(sz);
  fread(buf,1,sz,PEER_FILE);
  fclose(PEER_FILE);
  printf("2\n");
  fflush(stdout);

  int c = 0;
  int offset = 0;
  while (offset < sz)
  {
    if (*(buf+offset) == ',') c++;
    offset++;
  }

  printf("3\n");
  fflush(stdout);
  free(buf);
  return c;
}
