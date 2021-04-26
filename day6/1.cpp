//Sending signal from one thread to another thread
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
using namespace std;

pthread_t t1,t2;

void signal_callback(int signum){
    cout<<"Signal was received by the callback function"<<endl;
    return;
}

void* sendSignal(void* arg){
    cout<<"Thread 2: Sending a signal to thread 1"<<endl;
    int res = pthread_kill(t1,0);
    //cout<<res<<endl;
    //if the 2nd part is 0, and the return value is 0, it means that the signal has been successfully sent to the required thread
    int result = pthread_kill(t1,SIGUSR1);
    if(result < 0){
        perror("pthread_kill failed");
        exit(1);
    }
    pthread_exit((void*)0);
}

void* receiveSignal(void* arg){
  signal(SIGUSR1,signal_callback);
    sleep(1);
    cout<<"Thread 1: Received a signal from thread 2"<<endl;
    pthread_exit((void*)0);
}

int main()
{
    int result,thread_parameter=1;

    result = pthread_create(&t1,NULL,receiveSignal,(void*)&thread_parameter);
    if(result < 0)
    {
        perror("Thread creation failed");
        exit(1);
    }
    //sleep(1);
    result = pthread_create(&t2,NULL,sendSignal,(void*)&thread_parameter);
    if(result < 0){
        perror("Thread creation failed");
        exit(1);
    }
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    return 0;
}
