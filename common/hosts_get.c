#include <mixnet.h>

struct host
{
  char ip_addr[32];
  unsigned short port;
  RSA *key;
};

host *hosts_get(int idx)
{
  printf("get!\n");
  printf("1\n");
  FILE *HOSTS_FILE = fopen("/usr/etc/mixnet/hosts","r+");

  fseek(HOSTS_FILE,0,SEEK_END);
  int size = ftell(HOSTS_FILE);
  rewind(HOSTS_FILE);
  char *hosts = (char*)malloc(size);
  fread(hosts,1,size,HOSTS_FILE);

  int c = 0;
  char *comma = hosts;

  while (c < idx)
  {
    comma = strstr(comma,",");
    c+=1;
  }
  char *semi = strstr(comma+1,":");

  char *addr = (char*)malloc(semi-comma-1);

  memcpy(addr,comma,semi-comma);
  char *end = strstr(semi,",");
  char *port;
  if (end==NULL)
  {
    port = (char*)malloc(strlen(semi));
    memcpy(port,semi+1,strlen(semi)-1);
  } else
  {
    port = (char*)malloc(end-semi);
    memcpy(port,semi+1,end-semi);
  }

  //printf("addr: %s:%s id: %i\n",addr,port,c);
  char *path = (char*)malloc(1024);
  sprintf(path,"/usr/etc/mixnet/keys/%i.pem",c);
  FILE *keyfile = fopen(path,"r+");
  RSA *key = RSA_new();
  PEM_read_RSAPublicKey(keyfile,&key,NULL,NULL);

  host *ret = (host*)malloc(sizeof(host));
  sprintf(&(ret->ip_addr[0]),"%s",addr);
  ret->port = atoi(port);
  ret->key = key;

  free(path);
  fclose(HOSTS_FILE);
  return ret;
}
