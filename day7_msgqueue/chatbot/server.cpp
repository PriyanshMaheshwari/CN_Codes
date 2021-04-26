#include <time.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/msg.h>
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

key_t key;
int msgid;

struct mesg_buffer {
    long mesg_type;
    char mesg_buff[100];
} m1,m2,m3;

struct mesg_buffer2{
    long mesg_type;
    int val;
} p[4],sender[3];

void* thread1(void*){
  int cnt = 1;
  while(1){
    msgrcv(msgid, &m1, sizeof(m1), cnt, 0);
    cout << "Recieved : " << m1.mesg_buff << endl;
    for(int i=1;i<=3;i++){
      if(i!=cnt){
        m1.mesg_type = p[i].val;
        msgsnd(msgid,&m1,sizeof(m1),0);
      }
    }
  }
}

void* thread2(void*){
  int cnt = 2;
  while(1){
    msgrcv(msgid, &m2, sizeof(m2), cnt, 0);
    cout << "Recieved : " << m2.mesg_buff << endl;
    for(int i=1;i<=3;i++){
      if(i!=cnt){
        m2.mesg_type = p[i].val;
        msgsnd(msgid,&m2,sizeof(m2),0);
      }
    }
  }
}

void* thread3(void*){
  //cout << "go";
  int cnt = 3;
  while(1){
  //  cout << "pp";
    msgrcv(msgid, &m3, sizeof(m3), cnt, 0);
    cout << "Recieved : " << m3.mesg_buff << endl;
    for(int i=1;i<=3;i++){
      if(i!=cnt){
        m3.mesg_type = p[i].val;
        msgsnd(msgid,&m3,sizeof(m3),0);
      }
    }
  }
}

int main()
{

    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);
    //  msgctl(msgid, IPC_RMID, NULL);
    msgrcv(msgid, &p[1], sizeof(p[1]), 1, 0);
    msgrcv(msgid, &p[2], sizeof(p[2]), 2, 0);
    msgrcv(msgid, &p[3], sizeof(p[3]), 3, 0);
    for(int i=1;i<=3;i++){
      cout << "Process " << i << " : " << p[i].val << endl;
    }
    for(int i=1;i<=3;i++){
      sender[i].mesg_type = p[i].val;
      sender[i].val = getpid();
      msgsnd(msgid, &sender[i], sizeof(sender[i]), 0);
    }
    cout << "Server id sent to all : " <<getpid() << endl;

    cout << "Server Starts" << endl;

     pthread_t t1,t2,t3;
     pthread_create(&t1,NULL,thread1,NULL);
     pthread_create(&t2,NULL,thread2,NULL);
     pthread_create(&t3,NULL,thread3,NULL);

     pthread_join(t1,NULL);pthread_join(t3,NULL);pthread_join(t2,NULL);
}
