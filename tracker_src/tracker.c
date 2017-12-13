#include <mixnet.h>

extern void track(char *msg, int len, struct sockaddr_in from);

void tracker(int fd, struct sockaddr sa)
{
  printf("Tracker running on port %i\n",tracker_port); fflush(stdout);
  while(1)
  {
    struct sockaddr_in from;
    int salen = sizeof(struct sockaddr_in);
    size_t sz = sizeof(char)*4096;
    char *buf = (char*)malloc(sz);
    int bytes;
    bytes = (int)recvfrom(fd,(void*)buf,sz,0,(struct sockaddr *)&from,&salen);
    if (bytes < 0)
    {
      close(fd);
      mn_error("tracker: error receiving bytes");
    }
    track(buf,bytes,from);
  }
}
