#include <mixnet.h>

extern void tracker(int fd, struct sockaddr sa);

void start()
{
  tracker_fd = create_socket(AF_INET,SOCK_DGRAM,tracker_addr,tracker_port, &tracker_sa);
  fclose(fopen("/usr/etc/mixnet/peer","w+"));

  pid_t tracker_pid;
  tracker_pid=fork();
  if (tracker_pid==0)
  {
    if (!verbose) freopen("/usr/etc/mixnet/tracker_out","w+",stdout);
    if (!verbose) freopen("/usr/etc/mixnet/tracker_err","w+",stderr);
    tracker(tracker_fd,tracker_sa);
  } else
  {
    FILE *pid_file = fopen("/usr/etc/mixnet/tracker_pid","w+");
    fprintf(pid_file,"%d",tracker_pid);
    fclose(pid_file);
  }
}
