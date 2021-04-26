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

void PtoC(int mysignal){
  cout << "Parent to Child" << endl;
}

void CtoP(int mysignal){
  cout << "Child to Parent" << endl;
}

int main(){
  int k =1;
  //kill(getpid(),SIGKILL);


  pid_t pid = fork();
  //cout << pid << endl;
  if(pid > 0){
    //sleep(1);

    signal(SIGUSR2,CtoP);
    sleep(1);
    kill(pid,SIGUSR1);
    waitpid(pid,0,0);
  }
  else{
    signal(SIGUSR1,PtoC);
   sleep(1);
    kill(getppid(),SIGUSR2);
  }
}
