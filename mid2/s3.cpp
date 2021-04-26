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
#include<bits/stdc++.h>
using namespace std;

#define CONTROLLEN CMSG_LEN(sizeof(int))
static struct cmsghdr *cmptr = NULL;
char *path = "./fsock3";

int max(int x, int y)
{
    if (x > y)
        return x;
    return y;
}
int recv_fd(int fd) {

    struct iovec iov[1];
    char ptr[2];
    int newfd;

    struct msghdr m;

    iov[0].iov_base = ptr;
    iov[0].iov_len = sizeof(ptr);
    m.msg_iov = iov;
    m.msg_iovlen = 1;
    m.msg_name = NULL;
    m.msg_namelen = 0;


    cmptr = (cmsghdr *)malloc(CONTROLLEN);
    m.msg_control = cmptr;
    m.msg_controllen = CONTROLLEN;

    if(recvmsg(fd, &m, 0) < 0)
    {
        perror("recvmsg");
        return -1;
    }

    newfd = *(int *)CMSG_DATA(cmptr);

    return newfd;
}


int cli_conn(char *name)
{
    int fd, len;
    struct sockaddr_un u, su;

    if((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }
    int opt=1;
    if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(1);
    }

    unlink(name);
    u.sun_family = AF_UNIX;
    strcpy(u.sun_path, name);
    len = offsetof(struct sockaddr_un, sun_path) + strlen(name);
    if(bind(fd, (struct sockaddr*)&u, len))
    {
        perror("bind");
        exit(1);
    }

    su.sun_family = AF_UNIX;
    strcpy(su.sun_path, path);
    len = offsetof(struct sockaddr_un, sun_path) + strlen(path);
    if(connect(fd, (struct sockaddr*)&su, len) < 0)
    {
        perror("connect");
        exit(1);
    }

    return fd;
}

struct sockaddr_in address,address2;
int opt = 1;
int addrlen = sizeof(address);
int addrlen2 = sizeof(address2);
char buffer2[1024] = {0};
//
// void *thread2(void *i){
//   int nsfd = *((int *) i);
//   cout << "Started thread in server s1" << endl;
//   char buffer [1024] = "s1:";
//   int read = recv( nsfd , buffer2, 1024, 0);
//   buffer2[read] = '\0';
//   printf("message recv : %s\n",buffer2);
//   fgets(buffer2,1024,stdin);
//   strcat(buffer,buffer2);
//   send(nsfd , buffer , strlen(buffer), 0 );
//   buffer[strlen(buffer)] = '\0';
//   printf("message sent : %s\n",buffer);
// }

int main(){
    int ufd, rfd1,rfd2,rfd3,nready,nsfd,nsfd2;
    char buffer[1024];
    char *name = "./csock";
    fd_set rset;
    ssize_t n;
    socklen_t len;
    ufd = cli_conn(name);
    struct sockaddr_in cliaddr;
    pid_t child;
    char* message = "Hello Client";
// int fd = recv_fd(ufd);cout << fd << endl;
}
