#include <thread>
#include <sys/poll.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <bits/stdc++.h>
using namespace std;
#define PORT 8080
#define PORT2 10000
int sfd,sfd2;
struct sockaddr_in address,address2;
int opt = 1;
int addrlen = sizeof(address);
int addrlen2 = sizeof(address2);
char buffer2[1024] = {0};

void *thread1(void *i){
  int nsfd = *((int *) i);
  cout << "Started thread 1" << endl;
  char buffer [1024] = "1:";
  int read = recv( nsfd , buffer2, 1024, 0);
  buffer2[read] = '\0';
  printf("message recv : %s\n",buffer2);
  fgets(buffer2,1024,stdin);
  strcat(buffer,buffer2);
  send(nsfd , buffer , strlen(buffer), 0 );
  buffer[strlen(buffer)] = '\0';
  printf("message sent : %s\n",buffer);
}

void *thread2(void *i){
  int nsfd = *((int *) i);
  cout << "Started thread 2" << endl;
  char buffer [1024] = "2:";
  int read = recv( nsfd , buffer2, 1024, 0);
  buffer2[read] = '\0';
  printf("message recv : %s\n",buffer2);
  fgets(buffer2,1024,stdin);
  strcat(buffer,buffer2);
  send(nsfd , buffer , strlen(buffer), 0 );
  buffer[strlen(buffer)] = '\0';
  printf("message sent : %s\n",buffer);
}

int main(int argc, char const *argv[]){
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
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(sfd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((sfd2 = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    address2.sin_family = AF_INET;
    address2.sin_addr.s_addr = INADDR_ANY;
    address2.sin_port = htons( PORT2 );

    // Forcefully attaching socket to the port 8080
    if (bind(sfd2, (struct sockaddr *)&address2,
                                 sizeof(address2))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(sfd2, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    struct pollfd pfds[2];
    while (1) {
      pfds[0].fd = sfd;
      pfds[0].events = POLLIN;

      pfds[1].fd = sfd2;
      pfds[1].events = POLLIN;

      poll(pfds,2,500);
      if(pfds[0].revents & POLLIN){
        int nsfd;
        if ((nsfd = accept(sfd, (struct sockaddr *)&address,
                           (socklen_t*)&addrlen))<0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        pthread_t t1;
        int *ns = new int;
        *ns = nsfd;
        pthread_create(&t1,NULL,thread1,ns);
      }
      if(pfds[1].revents & POLLIN){
        int nsfd;
        if ((nsfd = accept(sfd2, (struct sockaddr *)&address2,
                           (socklen_t*)&addrlen2))<0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        pthread_t t1;
        int *ns = new int;
        *ns = nsfd;
        pthread_create(&t1,NULL,thread2,ns);
      }
    }

    return 0;
  }
