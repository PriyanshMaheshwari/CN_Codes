#include<iostream>
#include<unistd.h>
#include <stdio.h>
#include<cstring>
using namespace std;

int rfd,wfd;

void* writethreadchi(void*){
    int value=0;
    int result;
   while(1){
     //close(fd[0]);
     cout << "Enter the value for chi : ";
     cin >> value;
     result=write(wfd,&value,sizeof(int));
      if (result==-1){
           perror ("write error");
           exit (2);
       }
        cout<<"Writing from Thread1 in pipe1 : "<<value<<"\n";
        // value++;
        // if(value>26)
        // value=1;
        sleep(1);
   }
}

void* readthreadchi(void*){
   int value=0;
   int result;
   while(1){
     //close(fd[1]);
     sleep(1);
     result=read(rfd,&value,sizeof(int));
      if (result==-1){
           perror ("read error");
           exit (2);
       }
        cout<<"Reading from Thread2 : "<<value<<"\n";
   }
}

int main(){

	char buffer1[1024];
	char buffer2[1024];
  rfd=dup(STDIN_FILENO);
  wfd=dup(STDOUT_FILENO);
	int t=2;
	while(t--)
	{
		read(rfd,buffer1,1024);
    dup2(7,STDIN_FILENO);
dup2(8,STDOUT_FILENO);
    cout << "Read by child : ";
    pthread_t t1,t2;
    pthread_create(&t1,NULL,readthreadchi,NULL);
    pthread_create(&t2,NULL,writethreadchi,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
	}
	close(rfd);
	close(wfd);

}
