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

struct mesg_buffer {
    long mesg_type;
    char mesg_buff[100];
} m1,m2,m3;

int main()
{
    key_t key;
    int msgid;
    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);


    m1.mesg_type = 1;
    fgets(m1.mesg_buff,INT_MAX,stdin);
    m2.mesg_type = 3;
    fgets(m2.mesg_buff,INT_MAX,stdin);
    m3.mesg_type = 2;
    fgets(m3.mesg_buff,INT_MAX,stdin);

    msgsnd(msgid, &m2, sizeof(m2), 0);
    msgsnd(msgid, &m1, sizeof(m2), 0);
    msgsnd(msgid, &m3, sizeof(m2), 0);

    cout << "Data sent to all" << endl;

    return 0;
}
