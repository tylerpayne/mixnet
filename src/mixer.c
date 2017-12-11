#include <mixnet.h>

struct mix_t
{
  int fd;
  struct sockaddr_in sa;
  char *msg;
  int len;
};

void mixer(int fd, struct sockaddr sa)
{
  printf("Mixer running on port %i\n",mixer_port); fflush(stdout);
  while(1)
  {
    struct sockaddr_in from;
    size_t sz = sizeof(char)*4096;
    char *buf = (char*)malloc(sz);
    int bytes;
    bytes = (int)recvfrom(fd,(void*)buf,sz,0,(struct sockaddr*)&from,NULL);
    bytes = strlen(buf);
    if (bytes < 0)
    {
      close(fd);
      mn_error("mixer: error receiving bytes");
    }
    pthread_t mix_thread;
    mix_t m = {fd,from,buf,bytes};
    pthread_create(&mix_thread,NULL,mix,(void*)&m);
  }
}
