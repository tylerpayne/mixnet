#include <mixnet.h>

void stop()
{
  FILE *pid_file = fopen("/etc/mixnet/mixer_pid","r+");
  fseek(pid_file,0,SEEK_END);
  long sz = ftell(pid_file);
  fseek(pid_file,0,SEEK_SET);
  char cpid[sz];
  fread(&cpid[0],sz,1,pid_file);
  int pid = atoi(&cpid[0]);
  kill(pid,9);
  fclose(pid_file);
  remove("/etc/mixnet/mixer_pid");

  pid_file = fopen("/etc/mixnet/peeler_pid","r+");
  fseek(pid_file,0,SEEK_END);
  sz = ftell(pid_file);
  fseek(pid_file,0,SEEK_SET);
  cpid[sz];
  fread(&cpid[0],sz,1,pid_file);
  pid = atoi(&cpid[0]);
  kill(pid,9);
  fclose(pid_file);
  remove("/etc/mixnet/peeler_pid");
}
