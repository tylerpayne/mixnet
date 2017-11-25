#include <mixnet.h>

void mixer(int fd, struct sockaddr sa)
{
  while(1)
  {
    int cfd = accept(fd,NULL,NULL);
    if (cfd < 0)
    {
      close(fd);
      mn_error("relay: accept failed");
    }
    size_t sz = sizeof(char)*1024;
    char *buf = (char*)malloc(sz);
    int bytes = recv(cfd,(void*)buf,sz,0);
    if (bytes < 0)
    {
      close(cfd);
      close(fd);
      mn_error("relay: rror receiving bytes");
    }
    printf("received: %s",buf);
    //Create a mixchain
  }
}
