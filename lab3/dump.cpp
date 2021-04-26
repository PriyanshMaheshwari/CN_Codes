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
int main(){
    sem_unlink(S12);
    sem_unlink(S23);
    sem_unlink(S34);
    sem_unlink(S41);
    key_t key;
    int msgid;
      key = ftok("progfile", 65);
      msgid = msgget(key, 0666 | IPC_CREAT);
       msgctl(msgid, IPC_RMID, NULL);
}
