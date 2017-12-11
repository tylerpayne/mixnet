#include <mixnet.h>

void handle_tracker_sigkill(int sig)
{
  close(tracker_fd);
  exit(0);
}
