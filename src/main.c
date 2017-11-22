#include <mixnet.h>

int main(int argc, char **argv)
{
  argv[0] = "mixnet";
  if (argc < 2) mn_error("too few arguments");

  if (signal(SIGCHLD,handle_sigchild) == SIG_ERR) mn_error("failed to regester handler for SIGCHLD");

  if (strcmp(argv[1],"start")==0) start();
  else if (strcmp(argv[1],"stop")==0) stop();
  else if (strcmp(argv[1],"setup")==0)
  {
    if (argc < 3) mn_error("too few arguments");
    setup(argv[2]);
  } else mn_error("bad input arguments");

  return 0;
}
