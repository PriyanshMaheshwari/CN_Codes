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
#include <stdio.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/un.h>
#include<bits/stdc++.h>
using namespace std;

#define CONTROLLEN CMSG_LEN(sizeof(int))
static struct cmsghdr *cmptr = NULL;
char *path = "./fsock4";

struct sockaddr_in address,address2;
int opt = 1;
int addrlen = sizeof(address);
int addrlen2 = sizeof(address2);
char buffer[1024] = {0};

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
struct sockaddr_in inet_cliaddr1;
void func(int myhandler){
    int sfd = inet_serv_listen(8000);
    int len1 = sizeof(inet_cliaddr1);
    int nsfd=accept(sfd,(struct sockaddr*)&inet_cliaddr1,(socklen_t*)&len1);
      int valread = recv( nsfd , buffer, 1024, 0);
      send(nsfd , buffer , valread , 0 );
      buffer[valread] = '\0';
      printf("message recieved : %s\n",buffer );
      printf("message sent\n");
    raise(SIGUSR1);
}

int main(){
  cout << getpid() << endl;
  key_t key = ftok("/tmp",65);
    int shmid = shmget(key,1024,0666|IPC_CREAT);	//      X
    int* X = (int *) shmat(shmid,(void *)0,0);
    *X = getpid();

    int ufd, rfd1,rfd2,rfd3,nready,nsfd,nsfd2;
    char buffer[1024];
    char *name = "./c2sock";
    fd_set rset;
    ssize_t n;
    socklen_t len;
    signal(SIGUSR1,func);
    struct sockaddr_in cliaddr;
    pid_t child;
    raise(SIGUSR1);
    sleep(1000);
}
