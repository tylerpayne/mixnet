#include <mixnet.h>

void handle_mixer_sigkill(int sig)
{
  close(mixer_fd);
  exit(0);
}
