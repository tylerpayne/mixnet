#include <mixnet.h>

void start()
{
  char *localhost = "127.0.0.1";
  int relay_port = 5000, fwd_port = 5001;

  int relayfd,fwdfd;
  struct sockaddr relayaddr,fwdaddr;

  relayfd = create_socket(AF_INET,SOCK_STREAM,localhost,relay_port, &relayaddr);
  fwdfd = create_socket(AF_INET,SOCK_STREAM,localhost,fwd_port, &fwdaddr);

  if (listen(relayfd,10) < 0)
  {
    close(relayfd);
    mn_error("relay: listen failed");
  }

  if (listen(fwdfd,10) < 0)
  {
    close(relayfd);
    mn_error("fwd: listen failed");
  }

  pid_t relay_pid;
  relay_pid=fork();
  if (relay_pid==0)
  {
    relay(relayfd,relayaddr);
  } else
  {
    pid_t fwd_pid;
    fwd_pid = fork();
    if (fwd_pid == 0)
    {
      fwd(fwdfd,fwdaddr);
    }
  }
}
