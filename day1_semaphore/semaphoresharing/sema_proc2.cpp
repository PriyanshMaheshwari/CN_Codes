#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#define SNAME "/mysem2"
//sem_t mutex;
//
// void* thread(void* arg){
//     sem_wait(&mutex);
//     printf("\nEntered..\n");
//
//     sleep(4);
//
//     printf("\nJust Exiting...\n");
//     sem_post(&mutex);
// }


int main(){
  //printf("Lets go\n");
    //Initialize binary semaphore
    sem_t *sem = sem_open(SNAME, 0);
    // pthread_t t1,t2;
    sem_wait(sem);
    //pthread_t t1,t2;
    //Create thread 1
    //pthread_create(&t1,NULL,thread,NULL);
    // int val = 0;
    //  int x =  sem_getvalue(sem,&val);
    //  printf("%d\n",val);
     printf("Entering second process\n");
    sleep(3);
    //pthread_create(&t2,NULL,thread,NULL);
    // pthread_join(t1,NULL);
    //pthread_join(t2,NULL);;
    printf("Exiting second process\n");
    sem_post(sem);
    sleep(1);
    sem_wait(sem);
    printf("Entering second process\n");
   sleep(3);
   printf("Exiting second process\n");
   sem_post(sem);
   sem_destroy(sem);
    // pthread_create(&t2,NULL,thread,NULL);
    // pthread_join(t1,NULL);
    // pthread_join(t2,NULL);
    // sem_destroy(&mutex);
    return 0;
}
//Compile : gcc semaphore.cpp -lpthread -lrt
