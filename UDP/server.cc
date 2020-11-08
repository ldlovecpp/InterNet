#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
int main()
{
  int cfd = socket(AF_INET,SOCK_DGRAM,0);
  if(cfd==-1)
  {
    perror("socket()\n");
    return 1;
  }
  struct sockaddr_in addr;
  addr.sin_port = htons(9999);
  addr.sin_family = AF_INET;
  inet_aton("172.25.107.16",&addr.sin_addr);
  bind(cfd,(struct sockaddr*)& addr ,sizeof(addr));
  char buf[1024]={};
  struct sockaddr_in paddr;
  socklen_t len  =sizeof(paddr);
  while(1) 
  {
   memset(buf,0x00,1024);
   recvfrom(cfd,buf,1024,0,(struct sockaddr*)&paddr,&len);
   sendto(cfd,buf,strlen(buf),0,(struct sockaddr*)&paddr,len);
  }
}
