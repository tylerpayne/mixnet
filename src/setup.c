#include <mixnet.h>

void setup(char *name)
{
  struct stat st = {0};

  if (stat("/etc/mixnet", &st) == -1) mkdir("/etc/mixnet", 7777);
  printf("-1\n");
  FILE *namefile = fopen("/etc/mixnet/name","w+");
  printf("-2 %i\n",namefile==NULL);
  fwrite(name,strlen(name),1,namefile);
  printf("-3\n");
  fclose(namefile);
  printf("-4\n");
  KEY = generate_rsa_key();
}
