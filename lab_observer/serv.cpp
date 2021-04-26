#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stddef.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/un.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/poll.h>
#include <sys/time.h>
#include <unistd.h>
#include <bits/stdc++.h>
using namespace std;
#define PORT 5000
#define PORT2 6000
#define PORT3 7000
#define PORT4 8000
#define CONTROLLEN CMSG_LEN(sizeof(int))
static struct cmsghdr *cmptr = NULL;
int inet_serv_listen(int port)
{
    struct sockaddr_in servaddr;
    int sfd, len;
    int opt=1;
    if((sfd = socket(AF_INET, SOCK_STREAM, 0))==0)
    {
        perror("socket");
        exit(1);
    }
    if(setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(int)))
    {
        perror("setsockopt");
        exit(1);
    }
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    if(bind(sfd, (struct sockaddr*)&servaddr,sizeof(servaddr))<0)
    {
        perror("bind");
        exit(1);
    }

    if(listen(sfd,10)<0)
    {
        perror("listen");
        exit(1);
    }
    return sfd;
}
int main(){
  struct sockaddr_un s1_addr,s2_addr,s3_addr;
  struct sockaddr_in inet_cliaddr1,inet_cliaddr2,inet_cliaddr3;
  int len1,len2,len3 ,ufd1_s, nufd1, sfd1, nsfd1, sfd2, nsfd2, sfd3, sfd4, nsfd3, usfd,ufd2, nufd2,ufd3, nufd3,ufd4, nufd4;
  int ufd_s1,ufd_s3,ufd_s2;
  int  nufd_s1, nufd_s2, nufd_s3;
  fd_set cfd;

  sfd1=inet_serv_listen(PORT);
  sfd2=inet_serv_listen(PORT2);
  sfd3=inet_serv_listen(PORT3);
  while(1){
    nsfd1=accept(sfd1,(struct sockaddr*)&inet_cliaddr1,(socklen_t*)&len1);
    char buffer [1024] = "s1:";
    char buffer2[1024] = {0};
    int read = recv( nsfd1 , buffer2, 1024, 0);
    buffer2[read] = '\0';
    printf("message recv : %s\n",buffer2);
    fgets(buffer2,1024,stdin);
    strcat(buffer,buffer2);
    send(nsfd1 , buffer , strlen(buffer), 0 );
    buffer[strlen(buffer)] = '\0';
    printf("message sent : %s\n",buffer);

    nsfd2=accept(sfd2,(struct sockaddr*)&inet_cliaddr2,(socklen_t*)&len2);
    char buffer3 [1024] = "s2:";
    char buffer4[1024] = {0};
    read = recv( nsfd2 , buffer4, 1024, 0);
    buffer4[read] = '\0';
    printf("message recv : %s\n",buffer4);
    fgets(buffer4,1024,stdin);
    strcat(buffer3,buffer4);
    send(nsfd2 , buffer3 , strlen(buffer3), 0 );
    buffer3[strlen(buffer3)] = '\0';
    printf("message sent : %s\n",buffer3);

    nsfd1=accept(sfd3,(struct sockaddr*)&inet_cliaddr3,(socklen_t*)&len3);
    char buffer5 [1024] = "s1:";
    char buffer6[1024] = {0};
    read = recv( nsfd1 , buffer6, 1024, 0);
    buffer6[read] = '\0';
    printf("message recv : %s\n",buffer6);
    fgets(buffer6,1024,stdin);
    strcat(buffer5,buffer6);
    send(nsfd1 , buffer5 , strlen(buffer), 0 );
    buffer5[strlen(buffer5)] = '\0';
    printf("message sent : %s\n",buffer5);
  }
}
