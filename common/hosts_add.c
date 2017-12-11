#include <mixnet.h>

void hosts_add(struct sockaddr_in from, char *pubkey)
{
  printf("adding host\n");
  FILE *HOSTS_FILE = fopen("/usr/etc/mixnet/hosts","ab");

  char *from_addr = inet_ntoa(from.sin_addr);
  unsigned short port = ntohs(from.sin_port);

  //fseek(HOSTS_FILE,0L,SEEK_END);
  fprintf(HOSTS_FILE,"%s:%i,",from_addr,port);
  fflush(HOSTS_FILE);

  char *path = (char*)malloc(1024);
  struct stat st = {0};
  if (stat("/usr/etc/mixnet/keys", &st) == -1) mkdir("/usr/etc/mixnet/keys", 7777);
  sprintf(path,"/usr/etc/mixnet/keys/%i.pem",NHOSTS);

  FILE *keyfile = fopen(path,"w+");
  fwrite(pubkey,1,strlen(pubkey),keyfile);
  fflush(keyfile);

  NHOSTS = NHOSTS+1;

  free(path);
  fclose(HOSTS_FILE);
  fclose(keyfile);

}
