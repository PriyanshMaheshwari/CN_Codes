#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fstream>
#define SNAME "/mysemaphore"
sem_t mutex;
int main(){
   sem_t *sem = sem_open(SNAME,0);
    char buf[11];
   buf[10] = '\0';
     int k=2;
      while (k--){
      sem_wait(sem);
      read(0,buf,10);
      printf("From child : %s\n",buf);
      sem_post(sem);
      sleep(1);
    }
  return 0;
}
