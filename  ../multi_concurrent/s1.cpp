#include <sys/poll.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <bits/stdc++.h>
using namespace std;
char buffer2[1024];
int main(){
  int rfd,wfd;
  rfd=dup(STDIN_FILENO);
  wfd=dup(STDOUT_FILENO);
  dup2(12,STDIN_FILENO);
  dup2(13,STDOUT_FILENO);
  cout << "Started s1" << endl;
  char buffer [1024] = "1:";
  int read = recv( rfd , buffer2, 1024, 0);
  buffer2[read] = '\0';
  printf("message recv : %s\n",buffer2);
  fgets(buffer2,1024,stdin);
  strcat(buffer,buffer2);
  send(wfd , buffer , strlen(buffer), 0 );
  buffer[strlen(buffer)] = '\0';
  printf("message sent : %s\n",buffer);
  close(rfd);
}
