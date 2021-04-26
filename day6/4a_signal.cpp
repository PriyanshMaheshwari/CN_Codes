//Child is sending a signal to the parent and we will try to find the pid of the process sending the signal
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

pid_t pid1,pid2;

void signal_handler(int signum,siginfo_t *siginfo, void* context){
    int sender_pid = siginfo->si_pid;
    cout<<"PID of the sender process: "<<sender_pid<<endl;
    _exit(1);
    return;
}

int main()
{
    pid1 = fork();
    if(pid1 < 0){
        perror("Failed to create child process\n");
        exit(1);
    }
    if(pid1 > 0){
        //Parent Process
        static struct sigaction action;
        action.sa_sigaction = *signal_handler;
        sigemptyset(&action.sa_mask);
        sigaddset(&action.sa_mask,SIGTERM);
        sigaddset(&action.sa_mask,SIGINT);
        action.sa_flags = SA_SIGINFO;
        int status = sigaction(SIGUSR1,&action,NULL);
        if(status != 0){
            perror("Sigaction system call failed\n");
        }
        while(1){
            cout<<"Parent process is running\n";
            sleep(1);
        }
        exit(1);

    }
    else if(pid1 == 0)
    {
        //Child process
        cout<<"Child: Send a signal to Parent\n";
        cout<<"PID of the child process: "<<getpid()<<endl;
        kill(getppid(),SIGUSR1);
    }
}
