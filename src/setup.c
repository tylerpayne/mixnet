#include <mixnet.h>

void setup(char *name)
{
  printf("Setting up!\n");
  struct stat st = {0};
  if (stat("/usr/etc", &st) == -1) mkdir("/usr/etc", 7777);
  if (stat("/usr/etc/mixnet", &st) == -1) mkdir("/usr/etc/mixnet", 7777);
  FILE *namefile = fopen("/usr/etc/mixnet/name","w+");
  fwrite(name,strlen(name),1,namefile);
  fclose(namefile);
  KEY = generate_rsa_key();
  printf("Ready! Run \n  sudo mixnet start\nto start.\n  sudo mixnet stop\nto stop.\n");
}
