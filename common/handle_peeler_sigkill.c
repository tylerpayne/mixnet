#include <mixnet.h>

void handle_peeler_sigkill(int sig)
{
  char *up = "peeler_down";
  sendto(peeler_fd,up,strlen(up),0,&tracker_sa,sizeof(tracker_sa));
  close(peeler_fd);
  exit(0);
}
