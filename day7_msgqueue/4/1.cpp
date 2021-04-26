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
struct msgbuff
{
    long mtype;
    char mtext[100];
};
struct msgbuff msg;
int main()
{
    key_t key=ftok(".",64);
    int msgid=msgget(key,0666|IPC_CREAT);
    msg.mtype=1;
    int val = getpid();
    printf("%d\n",val);
    msgsnd(msgid,&msg,sizeof(msg),0);
    cout << "Message is Sent from p1" << endl;
    return 0;
}
