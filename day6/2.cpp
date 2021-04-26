//Send a signal from a thread of one process to another thread of a different process
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
pid_t pid,ppid;

void signal_callback_handler(int signum)
{
    cout<<"The handler function was called\n";
}

void* func1(void* arg){

    printf("Child thread: Sending a signal to parent thread\n");
    pthread_kill(t2,SIGUSR1);
    cout<<pthread_kill(t2,0)<<endl;
    pthread_exit((void*)0);
}

void* func2(void* arg){

    printf("Parent thread: Received a signal from the child thread\n");
    pthread_exit((void*)0);
}

int main()
{
    int pid = fork();
    int status1,status2;
    signal(SIGUSR1,signal_callback_handler);
    if(pid<0){
        perror("Fork() didn't work properly");
    }
    if(pid == 0){
        //child process
        status1 = pthread_create(&t1,NULL,func1,NULL);
        if(status1 < 0){
            perror("Thread creation failed\n");
            exit(1);
        }
        pthread_join(t1,NULL);
    }
    else
    {
        //parent process
        status2 = pthread_create(&t2,NULL,func2,NULL);
        if(status2 < 0){
            perror("Thread creation failed\n");
            exit(1);
        }
        pthread_join(t2,NULL);
    }
    return 0;
}
