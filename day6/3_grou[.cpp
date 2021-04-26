//Killing a group of process together
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

pid_t pids[4];

void child1_handler(int signum){
    cout<<"This is the child 1 handler function\n";
    sleep(1);
    _exit(1);
}

void child2_handler(int signum){
    cout<<"This is the child 2 handler function\n";
    sleep(1);
    _exit(1);
}

void child3_handler(int signum){
    cout<<"This is the child 3 handler function\n";
    sleep(1);
    _exit(1);
}

void parent_handler(int sig){
    cout<<"Parent was received a signal\n";
    sleep(1);
}
int main()
{
    pid_t pid = fork();
    if( pid > 0){

        pids[0]=getpid();
        signal(SIGUSR1,parent_handler);
        cout<<"Parent is running\n";
        //cout<<getpgid(getpid())<<endl;
        pid = fork();
        if(pid > 0){

            pid = fork();
            if(pid > 0){
                sleep(3);
                // This is the parent process that is running
                pid_t pgid = pids[3];
                for(int i=1;i<4;i++)
                {
                    setpgid(pids[i],pgid);
                    cout<<getpgid(pids[i])<<endl;
                }
                int status = killpg(getpgid(pids[1]),SIGUSR1);
                //cout<<status<<endl;
                if(status == -1){
                    perror("Error in sending signal to the group\n");
                    exit(1);
                }
            }
            else if(pid == 0){

                signal(SIGUSR1,child3_handler);
                while(1){
                    cout<<"Child 3 is running\n";
                    sleep(1);
                }
                //setpgid(getpid(),20000);
                //cout<<getpgid(getpid())<<endl;
                pids[3] = getpid();
            }
        }
        else if(pid == 0){
            signal(SIGUSR1,child2_handler);
            while(1){
                cout<<"Child 2 is running\n";
                sleep(1);
            }
            //setpgid(getpid(),20000);
            //cout<<getpgid(getpid())<<endl;
            pids[2]=getpid();
        }
    }
    else if(pid == 0)
    {
        pids[1]=getpid();
        signal(SIGUSR1,child1_handler);
        while(1){
            cout<<"Child 1 is running\n";
            sleep(1);
        }
        //setpgid(getpid(),20000);
        //cout<<getpgid(getpid())<<endl;
        sleep(1);
    }

    return 0;
}
