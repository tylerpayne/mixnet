#include <mixnet.h>

void peeler(int fd, struct sockaddr sa)
{
  printf("Peeler running!\n"); fflush(stdout);
  while(1)
  {
    int cfd = accept(fd,NULL,NULL);
    if (cfd < 0)
    {
      close(fd);
      mn_error("fwd: accept failed");
    }
    size_t sz = sizeof(char)*1024;
    char *buf = (char*)malloc(sz);
    int bytes = recv(cfd,(void*)buf,sz,0);
    if (bytes < 0)
    {
      close(cfd);
      close(fd);
      mn_error("fwd: error receiving bytes");
    }
    /*printf("received: %s",buf);
    fflush(stdout);
    // To Do: cast to mixchain*/
  }
}
