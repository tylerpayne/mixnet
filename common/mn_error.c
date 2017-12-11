#include <mixnet.h>

void mn_error(char *err)
{
  printf("#########################\n####  mixnet error:  ####\n#########################\n%s\n#########################\n",err);
  fflush(stdout);
  fflush(stderr);
  exit(1);
}
