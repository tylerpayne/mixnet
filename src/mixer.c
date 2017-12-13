#include <mixnet.h>

void mixer(int fd, struct sockaddr sa)
{
  printf("Mixer running on port %i\n",mixer_port); fflush(stdout);
  while(1)
  {
    struct sockaddr_in from;
    size_t sz = sizeof(char)*4096;
    char *buf = (char*)malloc(sz);
    int bytes;
    socklen_t from_len = 0;
    bytes = (int)recvfrom(mixer_fd,buf,sz,0,(struct sockaddr*)&from,&from_len);
    printf("got %i bytes\n",bytes);
    if (bytes < 0)
    {
      close(fd);
      mn_error("mixer: error receiving bytes");
    }
    mix(mixer_fd,from,buf,bytes);
  }
}
