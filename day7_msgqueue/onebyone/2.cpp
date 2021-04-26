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
#include <sys/ipc.h>
#include <sys/msg.h>
#include<stdlib.h>
using namespace std;
struct mesg_buffer {
    long mesg_type;
    char mesg_buff[100];
} message;

int main()
{
    key_t key;
    int msgid;
    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);

    for(int i=0;i<=2;i++){
        msgrcv(msgid, &message, sizeof(message), 1, 0);
        cout << "Message recieved" << " : " << message.mesg_buff << endl;
    }
  //  msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
