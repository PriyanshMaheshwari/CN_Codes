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
	sem_unlink(SNAME);
    sem_unlink(SNAME2);
	sem_t *s1 = sem_open(SNAME,O_CREAT|O_EXCL,0666,0);
	if(s1==SEM_FAILED){
		perror("sem_open");
		exit(EXIT_FAILURE);
	}
    sem_t *s2 = sem_open(SNAME2,O_CREAT|O_EXCL,0666,1);
    if(s2==SEM_FAILED){
		perror("sem_open");
		exit(EXIT_FAILURE);
	}
	key_t key = ftok("/tmp",65);
    int shmid = shmget(key,1024,0666|IPC_CREAT);	//      X
    int* X = (int *) shmat(shmid,(void *)0,0);     //  p1    p2
    *X = 1;																					//	   Y
    printf("Writing in X by proc1 : 1\n" );
	int pid=fork();
	if(pid>0){																											// sem_wait(s1)
		int t=4;
		while(t--){
			sem_wait(s1);
			key_t key2 = ftok("/y",60);
  		int shmid2 = shmget(key2,1000,0666|IPC_CREAT);
  		int* Y = (int *) shmat(shmid2,(void *)0,0);
  		int t = *Y;

  		printf("Reading in Y by proc 1 : %d\n",t);

  		t++;
	    printf("Writing in X by proc 1 : %d\n",t);
	    key_t key = ftok("/tmp",65);
	    int shmid = shmget(key,1024,0666|IPC_CREAT);
	    int* X = (int *) shmat(shmid,(void *)0,0);
	    *X = t;
	    sem_post(s2);
		}
	}
	else{
		static char *argv[]={"./a2.out",NULL};
     	execv(argv[0],argv);
     	exit(127);
	}
	sem_unlink(SNAME);
  sem_unlink(SNAME2);
	return 0;
}
