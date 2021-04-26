#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <poll.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;
#define PORT 8080

int sfd, nsfd, valread;
fd_set cfd,rfd; //current_socket;ready_socket

int main(int argc, char const *argv[])
{
    int sfd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char *hello = "Hello from server";

    // Creating socket file descriptor
    if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    // Forcefully attaching socket to the port 8080
    if (bind(sfd, (struct sockaddr *)&address,
                                 sizeof(address))<0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(sfd, 3) < 0){
        perror("listen");
        exit(EXIT_FAILURE);
    }
    int maxfd = 0;
    FD_ZERO(&cfd);
    FD_SET(sfd,&cfd);
    maxfd = sfd;

    struct timeval tv;
    tv.tv_sec=5;
    tv.tv_usec=0;
    FD_SET(nsfd,&cfd);
    maxfd = max(maxfd,nsfd);

    while(true){
      rfd = cfd;
      select(1024,&rfd,NULL,NULL,&tv);
      for(int i=0;i<=maxfd;i++){
        if(FD_ISSET(i,&rfd)){
          cout << "yo";
          if(i == sfd){
            //new_socket
            if ((nsfd = accept(sfd, (struct sockaddr *)&address,
                               (socklen_t*)&addrlen))<0){
                perror("accept");
                exit(EXIT_FAILURE);
            }
            cout << "less";
            FD_SET(nsfd,&cfd);
            maxfd = max(maxfd,nsfd);
          }
          else{
            char buffer[1024] = {0};
            valread = read( i , buffer, 1024);
            printf("%s\n",buffer );
            send(i , hello , strlen(hello) , 0 );
            printf("Hello message sent\n");
            FD_CLR(i,&cfd);
          }
        }
      }
   }
    return 0;
}
