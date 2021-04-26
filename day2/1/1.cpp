//READING FROM PARENT AND CHILD PROCESS
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include<fstream>
#include <fcntl.h>
const char* sem_name1 = "child";
const char* sem_name2 = "parent";
int main(){
	char buf[11];
	buf[10]='\0';
	int fd=open("text.txt",O_RDONLY);
	sem_unlink(sem_name1);
  sem_unlink(sem_name2);
	sem_t *mutex1 = sem_open(sem_name1,O_CREAT|O_EXCL,0666,1);
	if(mutex1==SEM_FAILED){
		perror("sem_open");
		exit(EXIT_FAILURE);
	}
    sem_t *mutex2 = sem_open(sem_name2,O_CREAT|O_EXCL,0666,0);
    if(mutex2==SEM_FAILED){
		perror("sem_open");
		exit(EXIT_FAILURE);
	}
  read(fd,buf,10);
	printf("Reading from Parent: %s\n",buf);
	int pid=fork();
	if(pid>0){
		int t=2;
		while(t--){
			sem_wait(mutex2);
			read(fd,buf,10);
			printf("Reading from Parent: %s\n",buf);
			sem_post(mutex1);
		}
		sem_post(mutex2);
	}
	else{
		int t=2;
		while(t--){
			sem_wait(mutex1);
			read(fd,buf,10);
			printf("Reading from Child: %s\n",buf);
			sem_post(mutex2);
		}
	}
	sem_unlink(sem_name1);
    sem_unlink(sem_name2);
	return 0;
}
