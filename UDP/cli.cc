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
  char buf[1024]={};
  while(fgets(buf,1024,stdin)) 
  {
   sendto(cfd,buf,strlen(buf),0,(struct sockaddr*)&addr,sizeof(addr));
   memset(buf,0x00,1024);
   recvfrom(cfd,buf,1024,0,NULL,NULL);
   printf("=>%s\n",buf);
  }
}
