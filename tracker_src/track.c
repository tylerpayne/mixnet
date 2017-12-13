  #include <mixnet.h>

void track(char *msg, int len, struct sockaddr_in from)
{
  char *from_addr = inet_ntoa(from.sin_addr);
  unsigned short port = ntohs(from.sin_port);
  char *entry = (char*)malloc(4096);

  sprintf(entry,"%s:%i",from_addr,port);
  printf("tracked %s from: %s\n",msg,entry);

  if (strncmp(msg,"peer_up",strlen("peer_up"))==0)
  {
    peer_add(from,msg+strlen("peer_up"),len-strlen("peer_up"));
  } else if (strncmp(msg,"peer_down",strlen("peer_down"))==0)
  {
    //hosts_remove(from);
  } else if (strncmp(msg,"query",strlen("query")==0))
  {


  }else
  {
    printf("Unrecognized message\n");
  }
}
