#include <mixnet.h>

void handle_sigchild(int sig)
{
  while (waitpid((pid_t)(-1), 0, WNOHANG) > 0) {}
}
