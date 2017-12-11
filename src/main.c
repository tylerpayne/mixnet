#include <mixnet.h>

int main(int argc, char **argv)
{
  argv[0] = "mixnet";
  if (argc < 2) mn_error("too few arguments");

  if (signal(SIGCHLD,handle_sigchild) == SIG_ERR) mn_error("failed to regester handler for SIGCHLD");

  //hanlde options
  verbose = 0b1;
  mixer_port = 5000;
  peeler_port = 5001;
  tracker_port = 5002;
  localhost = "127.0.0.1";
  tracker_addr = localhost;
  NHOSTS=0;
  for (int i = 2; i < argc; i++)
  {
    if (strncmp(argv[i],"-m",2) == 0)
    {
      if (strlen(argv[i]) > 2) mixer_port = atoi(argv[i]+2);
      else mixer_port = atoi(argv[i+1]);
    } else if (strncmp(argv[i],"-p",2) == 0)
    {
      if (strlen(argv[i]) > 2) peeler_port = atoi(argv[i]+2);
      else peeler_port = atoi(argv[i+1]);
    } else if (strncmp(argv[i],"-q",2) == 0)
    {
      verbose = 0b0;
    }
  }
  struct sockaddr_in *taddrin;
  taddrin = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
  taddrin->sin_family = AF_INET;
  taddrin->sin_port = htons(tracker_port);
  inet_pton(AF_INET,tracker_addr,&(taddrin->sin_addr));
  memcpy(&tracker_sa,(struct sockaddr*)taddrin,sizeof(struct sockaddr));

  if (strcmp(argv[1],"start")==0) start();
  else if (strcmp(argv[1],"stop")==0) stop();
  else if (strcmp(argv[1],"setup")==0)
  {
    if (argc < 3) mn_error("too few arguments");
    setup(argv[2]);
  } else mn_error("bad input arguments");

  return 0;
}
