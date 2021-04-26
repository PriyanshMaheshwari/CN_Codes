#include <iostream>
#include <string>
#include <sstream>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <errno.h>
#include <semaphore.h>
#include <fcntl.h>
#include <pthread.h>
using namespace std;

static struct sigaction siga;
int *shmX, *shmY;
key_t keyX, keyY;
int shmidX, shmidY;

int p1pid;
int main()
{
    // siga.sa_sigaction = *getInfoAboutSender;
    // siga.sa_flags |= SA_SIGINFO;
    cout << "D STARTED\n";
    sleep(1);
    keyX = ftok("/memory1", 65);
    shmidX = shmget(keyX, sizeof(int), 0666|IPC_CREAT);
    shmX = (int *)shmat(shmidX, NULL, 0);
    p1pid = *shmX;
    cout << "PID coming from server " << p1pid << "\n";
    int f = 1;
    *shmX = 0;
    while(1){
      cin >> f;
       if(f%2){
         cout << "Output in Group 1" << endl;
          kill(p1pid,SIGHUP);//s1,s2
          sleep(2);
       }
       else{
         cout << "Output in Group 2" << endl;
         kill(p1pid,SIGUSR2);//a,b
         sleep(2);
       }
       int t = *shmX;
       *shmX = ++t;

       cout << "Total signals by now : " << t << endl;
    }
}
