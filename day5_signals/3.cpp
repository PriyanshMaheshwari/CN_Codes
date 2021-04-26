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

int ppid;
int presentid;

void handler(int mysignal){
  key_t key2 = ftok("/y",60);
  int shmid2 = shmget(key2,1000,0666|IPC_CREAT);
  int* Y = (int *) shmat(shmid2,(void *)0,0);
  int t = *Y;

  printf("Reading in Y by proc 1 : %d\n",t);

  t++;
  printf("Writing in X by proc 1 : %d\n",t);
  key_t key = ftok("/tmp",65);
  int shmid = shmget(key,1024,0666|IPC_CREAT);
  int* X = (int *) shmat(shmid,(void *)0,0);
  *X = t;
  kill(ppid,SIGUSR2);
  sleep(1);
}


int main(){
  key_t key = ftok("/tmp",65);
  int shmid = shmget(key,1024,0666|IPC_CREAT);
  int* X = (int *) shmat(shmid,(void *)0,0);
  *X = 1;
  printf("Writing in X by proc1 : 1\n" );
  pid_t pid = fork();
  ppid = getppid();
  presentid = getpid();
  if(pid > 0){
    int k=4;
    signal(SIGUSR1,handler);
    mkfifo("lol",0666);
    int fd = open("lol",O_WRONLY);
    write(fd,&presentid,1024);
    close(fd);
    mkfifo("lol2",0666);
    int fd2 = open("lol2",O_RDONLY);
    read(fd2,&ppid,1024);
    close(fd2);
    presentid = getpid();
    kill(ppid,SIGUSR2);
    // cout << presentid << " " << ppid << "Proc1" << endl;
    // while(k--){
    //
    // }
    sleep(1000);
  }
  else{
    static char *argv[]={"./a2.out",NULL};
    execv(argv[0],argv);
    exit(127);
  }
}
