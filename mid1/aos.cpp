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
char *path4 = "./fsock4";


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
    struct sockaddr_un s1_addr,s2_addr,s3_addr;
    struct sockaddr_in inet_cliaddr1,inet_cliaddr2,inet_cliaddr3;
    int len1,len2,len3 ,ufd1_s, nufd1, sfd1, nsfd1, sfd2, nsfd2, sfd3, sfd4, nsfd3, usfd,ufd2, nufd2,ufd3, nufd3,ufd4, nufd4;
    int ufd_s1,ufd_s3,ufd_s2;
    int  nufd_s1, nufd_s2, nufd_s3;
    fd_set cfd;

    len1 = sizeof(s1_addr);
    len2 = sizeof(s2_addr);
    len3 = sizeof(s3_addr);

    ufd_s1=serv_listen(path1);
    ufd_s2=serv_listen(path2);
    ufd_s3=serv_listen(path3);
    //
    if((nufd1 = accept(ufd_s1, (struct sockaddr*)&s1_addr, (socklen_t*)&len1)) < 0)
    {
        perror("accept s1");
        exit(1);
    }
    else
        printf("Connection established with S1...\n");
    //
    if((nufd2 = accept(ufd_s2, (struct sockaddr*)&s2_addr, (socklen_t*)&len2)) < 0)
    {
        perror("accept s2");
        exit(1);
    }
    else
        printf("Connection established with S2...\n");
    //
    if((nufd3 = accept(ufd_s3, (struct sockaddr*)&s3_addr, (socklen_t*)&len3)) < 0)
    {
        perror("accept s3");
        exit(1);/* AF_UNIX connections finished */
    }
    else
        printf("Connection established with S3...\n");

    sfd1=inet_serv_listen(PORT);
    sfd2=inet_serv_listen(PORT2);
    sfd3=inet_serv_listen(PORT3);
    sfd4=inet_serv_listen(PORT4);


    FD_ZERO(&cfd);
    FD_SET(sfd1,&cfd);FD_SET(sfd2,&cfd);
    FD_SET(sfd3,&cfd);FD_SET(sfd4,&cfd);

    struct timeval tv;
    tv.tv_sec=5;
    tv.tv_usec=0;

    struct pollfd pfds[3];
    int maxfd = max({sfd1,sfd2,sfd3,sfd4});
    while(true){
      select(1024,&cfd,NULL,NULL,NULL);

          if(FD_ISSET(sfd1,&cfd)){
            nsfd1=accept(sfd1,(struct sockaddr*)&inet_cliaddr1,(socklen_t*)&len1);
            send_fd(nufd1, nsfd1);
            cout << "Fd sent to s1" << endl;
          }
          if(FD_ISSET(sfd2,&cfd)){
            nsfd2=accept(sfd2,(struct sockaddr*)&inet_cliaddr2,(socklen_t*)&len2);
            send_fd(nufd2, nsfd2);
            cout << "Fd sent to s2" << endl;
           }
           if(FD_ISSET(sfd3,&cfd)){
            nsfd3=accept(sfd3,(struct sockaddr*)&inet_cliaddr3,(socklen_t*)&len3);
            send_fd(nufd3, nsfd3);
            cout << "Fd sent to s3" << endl;
          }
          if(FD_ISSET(sfd4,&cfd)){
            key_t key = ftok("/tmp",65);
              int shmid = shmget(key,1024,0666|IPC_CREAT);	//      X
              int* X = (int *) shmat(shmid,(void *)0,0);
              pid_t pid = *X;
              cout << pid << endl;
              close(sfd4);
              kill(pid,SIGUSR1);
          }
      }

    unlink(path1);unlink(path2);unlink(path3);
}
