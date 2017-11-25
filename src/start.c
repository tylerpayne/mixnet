#include <mixnet.h>

void start()
{
  char *localhost = "127.0.0.1";
  int mixer_port = 5000, peeler_port = 5001;

  int mixer_fd,peeler_fd;
  struct sockaddr relayaddr,fwdaddr;

  mixer_fd = create_socket(AF_INET,SOCK_STREAM,localhost,mixer_port, &relayaddr);
  peeler_fd = create_socket(AF_INET,SOCK_STREAM,localhost,peeler_port, &fwdaddr);

  if (listen(mixer_fd,10) < 0)
  {
    close(mixer_fd);
    mn_error("relay: listen failed");
  }

  if (listen(peeler_fd,10) < 0)
  {
    close(peeler_fd);
    mn_error("fwd: listen failed");
  }

  pid_t relay_pid;
  relay_pid=fork();
  if (relay_pid==0)
  {
    mixer(mixer_fd,relayaddr);
  } else
  {
    pid_t fwd_pid;
    fwd_pid = fork();
    if (fwd_pid == 0)
    {
      peeler(peeler_fd,fwdaddr);
    }
  }
}
