#include <mixnet.h>

void peeler(int fd, struct sockaddr sa)
{
  printf("Peeler running on port %i\n",peeler_port); fflush(stdout);
  while(1)
  {
    struct sockaddr_in from;
    int from_len = sizeof(struct sockaddr_in);
    int sz = 4096;
    char *buf = (char*)malloc(sz);
    int bytes = recvfrom(fd,buf,sz,MSG_WAITALL,(struct sockaddr*)&from,&from_len);
    if (bytes < 0)
    {
      close(fd);
      mn_error("peeler: error receiving bytes");
    }
    printf("received %i bytes: %s\n",bytes,buf);
    fflush(stdout);
    peel(buf,bytes,fd);
  }
}
