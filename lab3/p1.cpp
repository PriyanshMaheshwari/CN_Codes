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
#incluSharedde <net/ethernet.h>
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
  sem_t *s12 = sem_open(S12,O_CREAT|O_EXCL,0666,0);
  sem_t *s41 = sem_open(S41,O_CREAT|O_EXCL,0666,0);
  sem_t *s23 = sem_open(S23,O_CREAT|O_EXCL,0666,0);
  sem_t *s34 = sem_open(S34,O_CREAT|O_EXCL,0666,0);
  cout << "Pid of process 1 : " << getpid() << endl;

  key_t key;
  int msgid;
  key = ftok("progfile", 65);
  msgid = msgget(key, 0666 | IPC_CREAT);

  m1.mesg_type = 1;
  m1.val = getpid();
//  cin >> m1.val;
  msgsnd(msgid, &m1, sizeof(m1), 0);
  sem_post(s41);
  sem_wait(s12);
  msgrcv(msgid, &m2, sizeof(m2), 1, 0);
  cout << "Process id recieved of p2 : " << m2.val<< endl;
  cout << "Enter the message to be sent : ";
  int i = 2;
  while(i--){
    m3.mesg_type = m2.val;
    if(i == 1)fgets(m3.mesg_buff,INT_MAX,stdin);
    msgsnd(msgid, &m3, sizeof(m3), 0);
    msgrcv(msgid, &m3, sizeof(m3), getpid(), 0);
    cout << "Message received from p4: " << m3.mesg_buff << endl;
  }
}
