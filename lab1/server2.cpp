/*
All the necessary commands are used except SIGSTOP.
For SIGSTOP I have use SIGUSR1.
Since it was written in documentation that SIGKILL and SIGSTOP are those
two signals which can't be overridden.
*/

#include <time.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/if_ether.h>
#include <net/ethernet.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/select.h>
#include <sys/un.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/socket.h>
#include <netinet/ether.h>
#include <netinet/udp.h>
#include <semaphore.h>
#include <bits/stdc++.h>
#include <sys/poll.h>
#include <sys/time.h>
#include<stdlib.h>
using namespace std;

int fd[4][2];
int inpfd[2];
FILE* fda,fdb;
int cur = 0;
int *shmX, *shmY;
key_t keyX, keyY;
int shmidX, shmidY;
struct pollfd pfds[2];
pid_t g1,g2;
pid_t cpid[4];

void handler(int mysignal){
  killpg(g2,SIGUSR1);
  killpg(g1,SIGCONT);
  sleep(1);
  cur = 0;
}
void handler2(int mysignal){
  killpg(g1,SIGUSR1);
  killpg(g2,SIGCONT);
  sleep(1);
  cur = 1;
}

void s1handlercont(int mysignal){
  cout << "S1 will start writing" << endl;
}
void s1handlerstop(int mysignal){
  cout << "S1 will stop writing" << endl;
}

void s2handlercont(int mysignal){
  cout << "S2 will start writing" << endl;
}
void s2handlerstop(int mysignal){
  cout << "S2 will stop writing" << endl;
}

void Ahandlercont(int mysignal){
  cout << "A will start writing" << endl;
}
void Ahandlerstop(int mysignal){
  cout << "A will stop writing" << endl;
}

void Bhandlercont(int mysignal){
  cout << "B will start writing" << endl;
}
void Bhandlerstop(int mysignal){
  cout << "B will stop writing" << endl;
}

int main(){
  pipe(fd[0]);pipe(fd[2]);
  pipe(fd[1]);pipe(fd[3]);
  char* myfifo1="myfifo11";
  mkfifo("myfifo11",0666);
  char* myfifo2="myfifo2";
  mkfifo("myfifo2",0666);
  inpfd[0] = open(myfifo1,O_RDONLY);
  inpfd[1] = open(myfifo2,O_RDONLY);
  signal(SIGHUP,handler);
  signal(SIGUSR2,handler2);

  pid_t pid1 = fork();
  cpid[0] = pid1;
  if(pid1==0){
    signal(SIGCONT,s1handlercont);
    signal(SIGUSR1,s1handlerstop);
    dup2(0,13);
    dup2(fd[0][0],0);
    int rfd;
    rfd=dup(STDIN_FILENO);
    //dup2(11,0);
    char s[80];
    while(1){
      int r = read(rfd,s,1024);
      cout << "this is s1 : " << s << endl;
    }
    dup2(13,0);
  }
  else{
    signal(SIGCONT,s2handlercont);
    signal(SIGUSR1,s2handlerstop);
    pid_t pid2 = fork();
    cpid[1] = pid2;
    if(pid2 == 0){
      dup2(0,13);
      dup2(fd[1][0],0);
      int rfd;
      rfd=dup(STDIN_FILENO);
      //dup2(11,0);
      char s[80];
      while(1){
        int r = read(rfd,s,1024);
        cout << "This is from S2 : " << s << endl;
      }
      dup2(13,0);
    }
    else{
      signal(SIGCONT,Ahandlercont);
      signal(SIGUSR1,Ahandlerstop);
      pid_t pid3 = fork();
      cpid[2] = pid3;
      if(pid3 == 0){
        dup2(0,13);
        dup2(fd[2][0],0);
        int rfd;
        rfd=dup(STDIN_FILENO);
        //dup2(11,0);
        char s[80];
        while(1){
          int r = read(rfd,s,1024);
          cout << "this is A : " << s << endl;
        }
        dup2(13,0);
      }
      else{
        signal(SIGCONT,Bhandlercont);
        signal(SIGUSR1,Bhandlerstop);
        pid_t pid4 = fork();
        cpid[3] = pid4;
        if(pid4 == 0){
          dup2(0,13);
          dup2(fd[3][0],0);
          int rfd;
          rfd=dup(STDIN_FILENO);
          char s[80];
          while(1){
            int r = read(rfd,s,1024);
            cout << "this is B : " << s << endl;
          }
          dup2(13,0);
        }
        else{
          keyX = ftok("/memory1", 65);
          shmidX = shmget(keyX, sizeof(int), 0666|IPC_CREAT);
          shmX = (int *)shmat(shmidX, NULL, 0);
          *shmX = getpid();
          cout <<getpid() << endl;
        //  sleep(3);

          //Making group
          g1 = cpid[0];
          setpgid(cpid[0],cpid[0]);setpgid(cpid[1],cpid[0]);
          g2 = cpid[2];
          setpgid(cpid[2],cpid[2]);setpgid(cpid[3],cpid[2]);
          //for(int i=0;i<4;i++)
          //cout << getpgid(cpid[i]) << " " << g1 << " " << g2 << endl;
          killpg(g1,SIGCONT);
          cout << "Ready to read client1" << endl;
          cout << "Ready to read client2" << endl;
          while(1){

            pfds[1].fd = inpfd[1];
            pfds[1].events = POLLIN;
            pfds[0].fd = inpfd[0];
            pfds[0].events = POLLIN;
            poll(pfds, 2, -1);

            if (pfds[0].revents & POLLIN) {
           //sleep(3);
              char s[80];
              read(inpfd[0],&s,80);
             cout << "Recieved Message in server : " << s << endl;
              if(cur%2==0){
                write(fd[0][1],&s,strlen(s)+1);
                write(fd[1][1],&s,strlen(s)+1);
              }
              else{
                write(fd[2][1],&s,strlen(s)+1);
                write(fd[3][1],&s,strlen(s)+1);
              }
            //  cout << "go";
            }
            else if (pfds[1].revents & POLLIN) {
              char s[80];
              read(inpfd[1],&s,80);
              cout << "Recieved Message in server : " << s << endl;
              if(cur%2==0){
                write(fd[0][1],&s,strlen(s)+1);
                write(fd[1][1],&s,strlen(s)+1);
              }
              else{
                write(fd[2][1],&s,strlen(s)+1);
                write(fd[3][1],&s,strlen(s)+1);
              }
            }
        //  cout << "yo";
          }
        }
      }
    }
  }
}
