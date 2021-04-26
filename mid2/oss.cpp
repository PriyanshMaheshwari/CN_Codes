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
char *path1 = "./fsock1";
char *path2 = "./fsock2";
char *path3 = "./fsock3";

struct sockaddr_un s1_addr,s2_addr,s3_addr;
struct sockaddr_in inet_cliaddr1,inet_cliaddr2,inet_cliaddr3;
int sfd1,nsfd1;
int len1,len2,len3;
int ufd_s[3];
int  nufd_s[3],nufd[3];
fd_set cfd;
pthread_t t[50];
int clno = 0;

int send_fd(int fd, int fd_to_send) {
    struct iovec iov[1];
    char ptr[2] = {0, 0};
    int newfd;

    struct msghdr m;

    iov[0].iov_base = ptr;
    iov[0].iov_len = 2;
    m.msg_iov = iov;
    m.msg_iovlen = 1;
    m.msg_name = NULL;
    m.msg_namelen = 0;

    cmptr = (cmsghdr*)malloc(CONTROLLEN);
    cmptr->cmsg_level = SOL_SOCKET;
    cmptr->cmsg_type = SCM_RIGHTS;
    cmptr->cmsg_len = CONTROLLEN;
    m.msg_control = cmptr;
    m.msg_controllen = CONTROLLEN;
    *(int *)CMSG_DATA(cmptr) = fd_to_send;

    if(sendmsg(fd, &m, 0) < 0)
    {
        perror("sendmsg");
        return -1;
    }

    return 0;
}

int serv_listen(char* path)
{

    int fd, len;
    struct sockaddr_un u;

    if((fd = socket(AF_UNIX, SOCK_STREAM, 0))==0)
    {
        perror("socket");
        exit(1);
    }
    int opt=1;
    if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(1);
    }
    unlink(path);
    u.sun_family = AF_UNIX;
    strcpy(u.sun_path, path);
    len = offsetof(struct sockaddr_un, sun_path) + strlen(path);
    if(bind(fd, (struct sockaddr*)&u, len)<0)
    {
        perror("bind");
        exit(1);
    }

    if(listen(fd, 10) < 0)
    {
        perror("listen");
        exit(1);
    }

    return fd;
}

void *func(void *i){
  int nsfd = *((int *) i);
  char buffer2 [1024];
  int read = recv( nsfd , buffer2, 1024, 0);
  buffer2[read] = '\0';
  printf("message recv : %s\n",buffer2);
  cout << "hi" << endl;
  vector<int> v;
  for(int i=1;i<read;i+=3){
    v.push_back(buffer2[i]-'0');
    v[v.size()-1] -= 1;
  }
  int x = clno-1;
  for(int i=0;i<v.size();i++)
    {send_fd(nufd[v[i]],nsfd);
  cout << "fd sent " << v[i] << endl;}
}
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

int main()
{

    len1 = sizeof(s1_addr);
    len2 = sizeof(s2_addr);
    len3 = sizeof(s3_addr);

    ufd_s[0]=serv_listen(path1);
    ufd_s[1]=serv_listen(path2);
    ufd_s[2]=serv_listen(path3);
    //
    if((nufd[0] = accept(ufd_s[0], (struct sockaddr*)&s1_addr, (socklen_t*)&len1)) < 0)
    {
        perror("accept s1");
        exit(1);
    }
    else
        printf("Connection established with S1...\n");
    //
    // if((nufd[1] = accept(ufd_s[1], (struct sockaddr*)&s2_addr, (socklen_t*)&len2)) < 0)
    // {
    //     perror("accept s2");
    //     exit(1);
    // }
    // else
    //     printf("Connection established with S2...\n");
    // //
    // if((nufd[2] = accept(ufd_s[2], (struct sockaddr*)&s3_addr, (socklen_t*)&len3)) < 0)
    // {
    //     perror("accept s3");
    //     exit(1);/* AF_UNIX connections finished */
    // }
    // else
    //     printf("Connection established with S3...\n");

    sfd1 = inet_serv_listen(PORT);
    while(1){
      nsfd1=accept(sfd1,(struct sockaddr*)&inet_cliaddr1,(socklen_t*)&len1);
      int *ns = new int;
      *ns = nsfd1;
      pthread_create(&t[clno++],NULL,func,ns);
    }

    unlink(path1);unlink(path2);unlink(path3);
}
