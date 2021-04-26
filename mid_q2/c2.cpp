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
#include <bits/stdc++.h>
using namespace std;
#define SNAME "q2"

struct mesg_buffer {
    long mesg_type;
    int msg_buff = 0;
} m1;
int msgid;
sem_t *s1;
bool f=true;
char* file;
int nextpid;
int fd;

void handler(int mysignal){
  int t = 2;
  cout << "Reading from ess : ";
  while(t--){
    char c;
    if(read(fd,&c,1))
      cout << c << " ";
  }
  cout << endl;
  if(f){
    struct msqid_ds buff;
    msgctl(msgid,IPC_STAT,&buff);
    if(buff.msg_qnum > 0){
      int x = nextpid;
      msgrcv(msgid, &m1, sizeof(m1), 0, 0);
      nextpid = m1.msg_buff;
      cout << "Message Recieved : " << nextpid << endl;
      m1.mesg_type = 1;
      m1.msg_buff = x;
      msgsnd(msgid,&m1,sizeof(m1),0);
      cout << "Message sent : " << x << endl;
      f = false;
      sleep(3);
    }
  }
  static int k = 0;
  if(k<100){
    k++;
    kill(nextpid,SIGUSR1);
  }
  sleep(3);
}

int main(){
  cout << "Starting c2 now : " << endl;
  fd = open("ess",O_RDONLY);
  nextpid = getpid();
  key_t key;
  key = ftok("progfile", 65);
  msgid = msgget(key, 0666 | IPC_CREAT);
  //s1 = sem_open(SNAME,O_CREAT|O_EXCL,0666,0);
  s1 = sem_open(SNAME,O_EXCL);
	if(s1==SEM_FAILED){
		perror("sem_open");
		exit(EXIT_FAILURE);
	}

//Saving name of ESS (taken as a normal file)
  key_t key2 = ftok("/tmp",65);
  int shmid = shmget(key,1024,0666|IPC_CREAT);
  file = (char*)shmat(shmid,(void *)0,0);
  cout << file << endl;

  m1.mesg_type = 2;
  m1.msg_buff = getpid();
  msgsnd(msgid,&m1,sizeof(m1),0);
  cout << "Message Sent : " << getpid() << endl;
  sleep(3);
   cout << "go";
   msgrcv(msgid, &m1, sizeof(m1), 1, 0);
   cout << "Message Recieved : " << m1.msg_buff << endl;
  nextpid = m1.msg_buff;

   signal(SIGUSR1,handler);
   raise(SIGUSR1);
   sleep(1000);
}
