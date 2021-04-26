#include<iostream>
#include<unistd.h>
#include <stdio.h>
#include<cstring>
#include<fcntl.h>
using namespace std;

int A[2];
int B[2];

void* readthreadpar(void*){
   int value=0;
   int result;
   while(1){
     //close(fd[1]);
     sleep(1);
     result=read(B[0],&value,sizeof(int));
      if (result==-1){
           perror ("read error");
           exit (2);
       }
        cout<<"Reading from Process 1 : "<<value<<"\n";
   }
}

void* writethreadpar(void*){
    int value=0;
    int result;
   while(1){
     cout << "Enter the value for par : ";
     cin >> value;
     result=write(A[1],&value,sizeof(int));
      if (result==-1){
           perror ("write error");
           exit (2);
       }

        cout<<"Writing from Thread1 in pipe1 : "<<value<<"\n";
        sleep(1);
   }
}


int main(){
	char buffer1[1024];
	char buffer2[1024];
	pipe(A);
	pipe(B);
  int stdinsave=dup(STDIN_FILENO);
  int stdoutsave=dup(STDOUT_FILENO);
	// dup2(0,10);
  // dup2(1,11);
	dup2(A[0],0);
	dup2(B[1],1);
	int c=fork();

	if(c>0)
	{
    close(A[0]);close(B[1]);
    dup2(stdinsave,STDIN_FILENO);
dup2(stdoutsave,STDOUT_FILENO);
    pthread_t t1,t2;
    pthread_create(&t1,NULL,readthreadpar,NULL);
    pthread_create(&t2,NULL,writethreadpar,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
	}
	else
	{
		execv("./p2",nullptr);

	}



}
