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
    char mesg_buff[100] = "C3 : ";
}messg2;

struct mesg_buffer2{
    long mesg_type;
    int val;
} m1,server;

void *writer(void *){
  while(1){
      mesg_buffer messg;
    messg.mesg_type = 3;
    char buffer[80];
    fgets(buffer,INT_MAX,stdin);
    strcat(messg.mesg_buff,buffer);
    msgsnd(msgid, &messg, sizeof(messg), 0);
    cout << "Message Written" << endl;
  }
}

void *reader(void *){
  while(1){
    msgrcv(msgid, &messg2, sizeof(messg2), getpid(), 0);
    cout << "Message Recieved : " << messg2.mesg_buff << endl;
  }
}

int main()
{

    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);

    m1.mesg_type = 3;
    m1.val = getpid();
    msgsnd(msgid, &m1, sizeof(m1), 0);
    cout << m1.val << endl;
    msgrcv(msgid, &server, sizeof(server), getpid(), 0);
    cout << "Server Id : " << server.val << endl;

    cout << "Client 3 Starts" << endl;

    pthread_t write_th,read_th;
  	pthread_create(&write_th,NULL,writer,NULL);
  	pthread_create(&read_th,NULL,reader,NULL);

  	pthread_join(write_th,NULL);
  	pthread_join(read_th,NULL);
}
