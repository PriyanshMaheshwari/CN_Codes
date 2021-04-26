#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex;

void* thread1(void* arg){
    sem_wait(&mutex);
    printf("\nEntered first..\n");

    sleep(3);

    printf("\nExiting first..\n");
    sem_post(&mutex);
}

void* thread2(void* arg){
    sem_wait(&mutex);
    printf("\nEntered second..\n");

    sleep(3);

    printf("\nExiting second...\n");
    sem_post(&mutex);
}


int main(){
    //Initialize binary semaphore
    sem_init(&mutex, 0, 1);
    pthread_t t1,t2;
    //Create thread 1
    pthread_create(&t1,NULL,thread1,NULL);
    // sleep(2);
    pthread_create(&t2,NULL,thread2,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    sem_destroy(&mutex);
    return 0;
}
//Compile : gcc semaphore.cpp -lpthread -lrt
