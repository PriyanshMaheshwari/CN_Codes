#include <stdio.h>
#include <unistd.h> //for fork system call
#include <sys/types.h>
#include <stdlib.h> //for exit system call
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <sys/poll.h>
#include <sys/time.h>
#include <assert.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/msg.h> // for msg queue
#include <string.h>
#include <bits/stdc++.h>
using namespace std;
struct mesg_buffer {
    long mesg_type;
    char mesg_buff[100];
} m1,m2,m3,m4,m5,m6;

int main()
{
    key_t key=ftok("tmp",64);
    int msgid=msgget(key,0666|IPC_CREAT);

    m1.mesg_type = 2;
    fgets(m1.mesg_buff,INT_MAX,stdin);
    m2.mesg_type = 2;
    fgets(m2.mesg_buff,INT_MAX,stdin);
    m3.mesg_type = 2;
    fgets(m3.mesg_buff,INT_MAX,stdin);

    msgsnd(msgid, &m2, sizeof(m2), 0);
    msgsnd(msgid, &m1, sizeof(m2), 0);
    msgsnd(msgid, &m3, sizeof(m2), 0);
    cout << "Message to P2 sent" << endl;

    m1.mesg_type = 3;
    fgets(m1.mesg_buff,INT_MAX,stdin);
    m2.mesg_type = 3;
    fgets(m2.mesg_buff,INT_MAX,stdin);
    m3.mesg_type = 3;
    fgets(m3.mesg_buff,INT_MAX,stdin);

    msgsnd(msgid, &m2, sizeof(m2), 0);
    msgsnd(msgid, &m1, sizeof(m2), 0);
    msgsnd(msgid, &m3, sizeof(m2), 0);
    cout << "Message to P3 sent" << endl;
}
