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
    bytes = (int)recvfrom(fd,(void*)buf,sz,0,(struct sockaddr*)&from,NULL);
    bytes = strlen(buf);
    if (bytes < 0)
    {
      close(fd);
      mn_error("mixer: error receiving bytes");
    }
    pid_t mix_pid = fork();
    if (mix_pid == 0)
    {
      mix(fd,from,buf,bytes);
    }
  }
}
