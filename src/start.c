#include <mixnet.h>

void start()
{
  KEY = RSA_new();
  FILE *pubkey = fopen("/etc/mixnet/pubkey.pem","r+");
  FILE *privkey = fopen("/etc/mixnet/privkey.pem","r+");
  PEM_read_RSAPublicKey(pubkey, &KEY, NULL,NULL);
  PEM_read_RSAPrivateKey(privkey, &KEY, NULL,NULL);
  fclose(pubkey);
  fclose(privkey);

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

  pid_t mixer_pid;
  mixer_pid=fork();
  if (mixer_pid==0)
  {
    freopen("/etc/mixnet/mixer_out","w+",stdout);
    freopen("/etc/mixnet/mixer_err","w+",stderr);
    mixer(mixer_fd,relayaddr);
  } else
  {
    FILE *pid_file = fopen("/etc/mixnet/mixer_pid","w+");
    fprintf(pid_file,"%d",mixer_pid);
    fclose(pid_file);
    pid_t peeler_pid;
    peeler_pid = fork();
    if (peeler_pid == 0)
    {
      freopen("/etc/mixnet/peeler_out","w+",stdout);
      freopen("/etc/mixnet/peeler_err","w+",stderr);
      peeler(peeler_fd,fwdaddr);
    } else
    {
      FILE *pid_file = fopen("/etc/mixnet/peeler_pid","w+");
      fprintf(pid_file,"%d",peeler_pid);
      fclose(pid_file);
    }
  }
}
