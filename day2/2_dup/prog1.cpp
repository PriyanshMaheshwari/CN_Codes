#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fstream>
#define SNAME "/mysemaphore"
int main(){
   char buf[11];
   buf[10] = '\0';
  int file=open("text.txt",O_RDONLY);
  sem_t *sem = sem_open(SNAME, O_CREAT, 0644, 1);
    if (sem == SEM_FAILED) {
    perror("ERROR:");
    exit(1);
    }
    
  int nfg;
  dup2(0,nfg);
  dup2(file,0);
   int c=fork();
  if(c>0){
      int k=2;
      while (k--){
      sleep(1);
      sem_wait(sem);
      read(file,buf,10);
      printf("From parent : %s\n",buf);
      sem_post(sem);
    }
  }
  else{
     static char* argv[]={"./prog2",NULL};
     execv(argv[0],argv);
  }
  dup2(nfg,0);
  return 0;
}
