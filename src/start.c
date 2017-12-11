#include <mixnet.h>

void start()
{
  RSAKEY = RSA_new();
  FILE *pubkey = fopen("/usr/etc/mixnet/pubkey.pem","r+");
  FILE *privkey = fopen("/usr/etc/mixnet/privkey.pem","r+");
  PEM_read_RSAPublicKey(pubkey, &RSAKEY, NULL,NULL);
  PEM_read_RSAPrivateKey(privkey, &RSAKEY, NULL,NULL);

  char *public_key = (char*)malloc(4096);
  fseek(pubkey,0,SEEK_END);
  int size = ftell(pubkey);
  rewind(pubkey);
  fread(public_key,1,size,pubkey);

  printf("RSA key check: %i\n",RSA_check_key(RSAKEY));
  fclose(pubkey);
  fclose(privkey);
  fflush(stdout);

  struct sockaddr mixer_addr,peeler_addr;

  mixer_fd = create_socket(AF_INET,SOCK_DGRAM,localhost,mixer_port, &mixer_addr);
  peeler_fd = create_socket(AF_INET,SOCK_DGRAM,localhost,peeler_port, &peeler_addr);

  //mixer(mixer_fd,mixer_addr);
  pid_t mixer_pid;
  mixer_pid=fork();
  if (mixer_pid==0)
  {
    if (!verbose) freopen("/usr/etc/mixnet/mixer_out","w+",stdout);
    if (!verbose) freopen("/usr/etc/mixnet/mixer_err","w+",stderr);
    if (signal(3,handle_mixer_sigkill) == SIG_ERR) mn_error("failed to regester handler for SIGKILL");
    time_t t = time(NULL);
    RAND_seed(&t,sizeof(time_t));
    RAND_poll();
    mixer(mixer_fd,mixer_addr);

  } else
  {
    FILE *pid_file = fopen("/usr/etc/mixnet/mixer_pid","w+");
    fprintf(pid_file,"%d",mixer_pid);
    fclose(pid_file);
    pid_t peeler_pid;
    peeler_pid = fork();
    if (peeler_pid == 0)
    {
      if (!verbose) freopen("/usr/etc/mixnet/peeler_out","w+",stdout);
      if (!verbose) freopen("/usr/etc/mixnet/peeler_err","w+",stderr);
      if (signal(3,handle_peeler_sigkill) == SIG_ERR) mn_error("failed to regester handler for SIGKILL");
      time_t t = time(NULL);
      RAND_seed(&t,sizeof(time_t));
      RAND_poll();
      peeler(peeler_fd,peeler_addr);
    } else
    {
      FILE *pid_file = fopen("/usr/etc/mixnet/peeler_pid","w+");
      fprintf(pid_file,"%d",peeler_pid);
      fclose(pid_file);

      char *up = (char*)malloc(4096);
      sprintf(up,"%s%s","peeler_up",public_key);
      sendto(peeler_fd,up,strlen(up),0,&tracker_sa,sizeof(tracker_sa));
      free(up);
      free(public_key);
    }
  }
}
