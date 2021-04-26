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
using namespace std;

int pid;

void handler(int mysignal){
  key_t key = ftok("/tmp",65);
  int shmid = shmget(key,1024,0666|IPC_CREAT);
  int* X = (int *) shmat(shmid,0,0);
  int t = *X;
  printf("Reading from X by proc 2 : %d\n",t);

  key_t key2 = ftok("/y",60);
  int shmid2 = shmget(key2,1000,0666|IPC_CREAT);
  int* Y = (int *) shmat(shmid2,(void *)0,0);
  t++;
  *Y = t;
  printf("Writing in Y by proc 2 : %d\n",t);
  kill(pid,SIGUSR1);
  sleep(1);
}

int main(){
  signal(SIGUSR2,handler);
  int k = 4;
  mkfifo("lol",0666);
  int fd = open("lol",O_RDONLY);
  read(fd,&pid,1024);
  close(fd);
  mkfifo("lol2",0666);
  int fd2 = open("lol2",O_WRONLY);
  int presentid = getpid();
  write(fd2,&presentid,1024);
  close(fd2);
  // cout << pid << " " << presentid << "Proc2" << endl;
  sleep(1);
}
