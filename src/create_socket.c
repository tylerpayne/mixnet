#include <mixnet.h>

//Returns sockfd, sets saddr
int create_socket(int domain, int type, char *ip_addr, int port, struct sockaddr *saddr)
{
  int sockfd;
  struct sockaddr_in sa;

  sockfd = socket(domain,type,0);
  if (sockfd < 0) mn_error("failed to create socket");

  sa.sin_family = domain;
  sa.sin_port = htons(port);
  sa.sin_addr.s_addr = inet_addr(ip_addr);

  if (saddr != NULL) memcpy(saddr,&sa,sizeof(sa));

  if ((bind(sockfd,(struct sockaddr *)&sa,sizeof(sa))) < 0)
  {
    close(sockfd);
    mn_error("bind failed");
  }
  return sockfd;
}
