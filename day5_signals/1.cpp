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

void handler(int mysignal){
  static int i = 0;
  i++;
  cout << "Called for " << i << " time" << endl;
  if(i==5){
    kill(getpid(),9);
    //raise(9)
  }
}

int main(){
  int k =1;
  //kill(getpid(),SIGKILL);
  signal(SIGINT,handler);
  while(1){
    cout << " k = " << k++ << endl;
    sleep(1);
  }
}
