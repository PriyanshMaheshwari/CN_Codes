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
#include <sys/msg.h>

using namespace std;

#define S12 "s12"
#define S41 "s41"
#define S23 "s23"
#define S34 "s34"

struct mesg_buffer {
    long mesg_type;
    int val;
} m1,m2;

struct mesg_buffer2 {
    long mesg_type;
    char mesg_buff[100];
} m3;

int main(){
  sem_t *s34 = sem_open(S34,O_EXCL);
  sem_t *s23 = sem_open(S41,O_EXCL);
  cout << "Process id of 3 : " << getpid() << endl;
  int x;
// sem_getvalue(s41,&x);
// cout << x << endl;
  key_t key;
  int msgid;
  key = ftok("progfile", 65);
  msgid = msgget(key, 0666 | IPC_CREAT);
  sem_wait(s34);
  msgrcv(msgid, &m2, sizeof(m2), 1, 0);
  cout << "Process id recieved of p4 : " << m2.val<< endl;
  m1.mesg_type = 1;
  m1.val = getpid();
  msgsnd(msgid, &m1, sizeof(m1), 0);
  sem_post(s23);

  int i=2;
  while(i--){
    msgrcv(msgid, &m3, sizeof(m3), getpid(), 0);
    cout << "Message received from p2: " << m3.mesg_buff << endl;
    m3.mesg_type = m2.val;
    msgsnd(msgid, &m3, sizeof(m3), 0);
  }
}
