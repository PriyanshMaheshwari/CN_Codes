//Using sigaction to find the pid of the process that send the signal
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

struct sigaction action;

void signal_callback_handler(int signum, siginfo_t* siginfo, void* context){
    cout<<"Handler function called\n";
    int sender_pid = siginfo->si_pid;
    cout<<sender_pid<<endl;
    //cout<<"PID of the process that send the signal:"<<pid_of_sender_process<<endl;
}

int main()
{
    // sigemptyset(&s);
    // sigaddset(&s,SIGTERM);
    // sigaddset(&s,SIGINT);
    action.sa_sigaction = *signal_callback_handler;
    sigemptyset(&action.sa_mask);
    sigaddset(&action.sa_mask,SIGTERM);
    sigaddset(&action.sa_mask,SIGINT);
    action.sa_flags = SA_SIGINFO;
    int status = sigaction(SIGUSR1,&action,NULL);
    if(status != 0){
        perror("Error in the sigaction system call\n");
        exit(1);
    }
    cout<<"PID of the parent process: "<<getpid()<<endl;
    raise(SIGUSR1);
    return 0;
}
