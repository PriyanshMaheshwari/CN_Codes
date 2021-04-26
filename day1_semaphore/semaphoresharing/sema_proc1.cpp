#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#define SNAME "/mysem2"
//sem_t mutex;
//
// void* thread(void* arg){
//     sem_wait(&sem);
//     printf("\nEntered..\n");
//
//     sleep(4);
//
//     printf("\nJust Exiting...\n");
//     //sem_post(&mutex);
// }


int main(){
    //Initialize binary semaphore
    sem_t *sem = sem_open(SNAME, O_CREAT, 0644, 1);
    if (sem == SEM_FAILED) {
    perror("ERROR:");// e.g. "ERROR: Permission denied" or similar
    exit(1);
    }
    printf("Entering first\n");
  //  int val = 0;
     // int x =  sem_getvalue(sem,&val);
     // printf("%d",val);
    // //sem_init(&mutex, 0, 1);
     sem_wait(sem);
     // x =  sem_getvalue(sem,&val);
     // printf("%d",val);
    // printf("Entering first\n" );
    //pthread_t t1,t2;
    //Create thread 1
    //pthread_create(&t1,NULL,thread,NULL);
    // system("./a2.out");
     pid_t pid = fork();
    if(pid == 0){
      static char *argv[]={"./a2.out",NULL};
      execv(argv[0],argv);
      exit(127);
    }
    else{
    //  waitpid(pid,0,0);
      sleep(5);
      //pthread_create(&t2,NULL,thread,NULL);
      // pthread_join(t1,NULL);
      //pthread_join(t2,NULL);
      printf("Exiting first\n" );
     sem_post(sem);
     sleep(1);
     sem_wait(sem);
     printf("Entering first process\n");
    sleep(3);
    printf("Exiting first process\n");
    sem_post(sem);
    sleep(5);
     sem_destroy(sem);
    }
    return 0;
}
//Compile : gcc sema_proc1.cpp -lpthread -lrt
