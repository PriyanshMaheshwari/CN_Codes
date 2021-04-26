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
  cout << "Started s2" << endl;
  char buffer [1024] = "2:";
  int read = recv( rfd , buffer2, 1024, 0);
  strcat(buffer,buffer2);
  send(wfd , buffer , read , 0 );
  buffer[read+2] = '\0';
  printf("message sent : %s\n",buffer);
  close(rfd);
}
