#include <mixnet.h>

struct peer
{
  char flag;
  struct sockaddr_in addr;
  char *public_key_str;
  RSA *key;
};

int main(int argc, char const *argv[]) {

  int sockfd;
  struct sockaddr sa;
  int peer_size = sizeof(struct peer);

  sockfd = create_socket(AF_INET,SOCK_DGRAM,"127.0.0.1",8009,&sa);

  struct sockaddr_in *addr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in *));
  addr->sin_family = AF_INET;
  addr->sin_addr.s_addr = inet_addr("127.0.0.1");
  addr->sin_port = htons(8009);

  struct peer h;
  h.flag = '1';
  h.addr = *addr;

  struct sockaddr_in *mn_addr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in *));
  mn_addr->sin_family = AF_INET;
  mn_addr->sin_addr.s_addr = inet_addr("127.0.0.1");
  mn_addr->sin_port = htons(5000);

  int payload_len = peer_size+strlen("Hello, world!");
  char *payload = (char* )malloc(payload_len);

  memcpy(payload,&h,peer_size);
  memcpy(payload+peer_size,"Hello, world!",strlen("Hello, world!"));

  sendto(sockfd,payload,payload_len,0,(struct sockaddr*)mn_addr,sizeof(struct sockaddr_in));
  printf("sending %i byte message \"%s\" to %s:%i via mixnet running at %s:%i\n",strlen("Hello, world!"),"Hello, world!",inet_ntoa(addr->sin_addr),ntohs(addr->sin_port),inet_ntoa(mn_addr->sin_addr),ntohs(mn_addr->sin_port));


  char *buf = malloc(1024*1024);
  struct sockaddr_in from = *(struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
  socklen_t from_len = sizeof(struct sockaddr_in);
  int bytes = (int)recvfrom(sockfd,buf,1024*1024,0,(struct sockaddr*)&from,&from_len);
  printf("got %i byte message: \"",bytes);
  fwrite(buf,1,bytes,stdout);
  printf("\". from %s:%i",inet_ntoa(from.sin_addr),ntohs(from.sin_port));
  printf("\n");
  fflush(stdout);


  return 0;
}
