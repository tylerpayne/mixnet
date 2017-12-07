#include <mixnet.h>

struct mix_t
{
  int fd;
  struct sockaddr sa;
  char *msg;
  int len;
};

void mixer(int fd, struct sockaddr sa)
{
  printf("Mixer running!\n"); fflush(stdout);
  while(1)
  {
    int cfd = accept(fd,NULL,NULL);
    if (cfd < 0)
    {
      close(fd);
      mn_error("mixer: accept failed");
    }
    size_t sz = sizeof(char)*4096;
    char *buf = (char*)malloc(sz);
    int bytes;
    bytes = (int)recv(cfd,(void*)buf,sz,0);
    bytes = strlen(buf);
    printf("bytes:%i\n",bytes);
    if (bytes < 0)
    {
      close(cfd);
      close(fd);
      mn_error("mixer: error receiving bytes");
    }
    pthread_t mix_thread;
    mix_t m = {cfd,sa,buf,bytes};
    //pthread_create(&mix_thread,NULL,mix,(void*)&m);
    mix((void*)&m);
  }
}
