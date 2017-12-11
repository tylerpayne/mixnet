#include <mixnet.h>

void hosts_remove(struct sockaddr_in from)
{
  printf("removing\n");
  FILE *HOSTS_FILE = fopen("/usr/etc/mixnet/hosts","r+");
  char *from_addr = inet_ntoa(from.sin_addr);
  unsigned short port = ntohs(from.sin_port);

  char *entry = (char*)malloc(64);
  sprintf(entry,"%s:%i",from_addr,port);

  int count = 0;
  fseek(HOSTS_FILE,0,SEEK_END);
  int sz = ftell(HOSTS_FILE);
  rewind(HOSTS_FILE);
  printf("sz: %i\n",sz);
  int begin=0,end=0;
  char *buf = (char*)malloc(1024);
  for (int o = 0; o < sz; o++)
  {
    end = o;
    fseek(HOSTS_FILE,o,SEEK_SET);
    fread(buf,1,1,HOSTS_FILE);
    if (strncmp(buf,",",1)==0)
    {
      printf(", %i\n",count);
      printf("%i-%i\n",begin,end);
      fseek(HOSTS_FILE,begin,SEEK_SET);
      fread(buf,1,end-begin,HOSTS_FILE);
      fseek(HOSTS_FILE,o,SEEK_SET);
      if(strcmp(buf,entry) == 0)
      {
        printf("match!\n");
        char *path = (char*)malloc(1024);
        sprintf(path,"/usr/etc/mixnet/keys/%i",count);
        remove(path);
        NHOSTS = NHOSTS - 1;
        memset(path,0,1024);
        char cbuf;
        printf("%i-%i\n",begin,end);
        for (int i = 0; i < sz; i++)
        {
          if (i >= end || i < begin)
          {
            fseek(HOSTS_FILE,i,SEEK_SET);
            fread(&buf,1,1,HOSTS_FILE);
            if (i >= end) fseek(HOSTS_FILE,i-(end-begin),SEEK_SET);
            fwrite(&buf,1,1,HOSTS_FILE);
          }
        }
        break;
      }
      count = count+1;
      begin = o;
    }
  }
  free(entry);
  fclose(HOSTS_FILE);
}
