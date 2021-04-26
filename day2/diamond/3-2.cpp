#include <stdio.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#define SNAME "code1"
#define SNAME2 "code2"
int main(){
    sem_t *s1 = sem_open(SNAME,O_EXCL);
    sem_t *s2 = sem_open(SNAME2,O_EXCL);
    int k = 4;
    while(k--){
      sem_wait(s2);

      key_t key = ftok("/tmp",65);
      int shmid = shmget(key,1024,0666|IPC_CREAT);
      int* X = (int *) shmat(shmid,0,0);
      int t = *X;
      printf("Reading from X by proc 2 : %d\n",t);

      key_t key2 = ftok("/y",60);
      int shmid2 = shmget(key2,1000,0666|IPC_CREAT);
      int* Y = (int *) shmat(shmid2,(void *)0,0);
      t++;
      *Y = t;
      printf("Writing in Y by proc 2 : %d\n",t);
      sem_post(s1);
   }
  key_t key = ftok("/tmp",65);
  int shmid = shmget(key,1024,0666|IPC_CREAT);
  key_t key2 = ftok("/y",60);
  int shmid2 = shmget(key2,1000,0666|IPC_CREAT);
  shmctl(shmid,IPC_RMID,NULL);
  shmctl(shmid2,IPC_RMID,NULL);

  return 0;
}
//Compile : gcc semaphore.cpp -lpthread -lrt
