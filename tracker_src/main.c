#include <mixnet.h>

int main(int argc, char const *argv[]) {
  argv[0] = "mixnet_tracker";
  if (argc < 2) mn_error("too few arguments");

  verbose = 0b1;
  tracker_port = 5002;
  localhost = "127.0.0.1";
  tracker_addr = localhost;


  for (int i = 2; i < argc; i++)
  {
    if (strncmp(argv[i],"-q",2) == 0)
    {
      verbose = 0b0;
    }
  }

  if (strcmp(argv[1],"start")==0) start();
  else if (strcmp(argv[1],"stop")==0) stop();
  else mn_error("bad input arguments");

  return 0;
}
