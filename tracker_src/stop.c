#include <mixnet.h>

void stop()
{
  FILE *pid_file = fopen("/usr/etc/mixnet/tracker_pid","r+");
  fseek(pid_file,0,SEEK_END);
  long sz = ftell(pid_file);
  fseek(pid_file,0,SEEK_SET);
  char cpid[sz];
  fread(&cpid[0],sz,1,pid_file);
  int pid = atoi(&cpid[0]);
  kill(pid,3);
  fclose(pid_file);
  remove("/usr/etc/mixnet/tracker_pid");
  remove("/usr/etc/mixnet/hosts");
}
