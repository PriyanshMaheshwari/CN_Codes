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
char *path = "./fsock2";

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
char buffer[1024] = {0};


void func(int *fd){
    int nsfd = *fd,valread;
    pid_t pid = fork();
    if(pid == 0){
      valread = recv( nsfd , buffer, 1024, 0);
      send(nsfd , buffer , valread , 0 );
      buffer[valread] = '\0';
      printf("message recieved : %s\n",buffer );
      printf("message sent\n");
    }
}

int main(){
    int ufd, rfd1,rfd2,rfd3,nready,nsfd,nsfd2;
    char buffer[1024];
    char *name = "./c2sock";
    fd_set rset;
    ssize_t n;
    socklen_t len;
    ufd = cli_conn(name);
    struct sockaddr_in cliaddr;
    pid_t child;
    char* message = "Hello Client";
    while(1){
    if((rfd1 = recv_fd(ufd)) < 0)
    {
        perror("recv_fd 1");
        exit(1);
    }
    else{
      int *ns = new int;
      *ns = rfd1;
      func(ns);
    }}
}
